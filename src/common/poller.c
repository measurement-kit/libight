/* libneubot/poller.c */

/*-
 * Copyright (c) 2013
 *     Nexa Center for Internet & Society, Politecnico di Torino (DAUIN)
 *     and Simone Basso <bassosimone@gmail.com>.
 *
 * This file is part of Neubot <http://www.neubot.org/>.
 *
 * Neubot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Neubot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Neubot.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <arpa/inet.h>
#include <sys/queue.h>

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef WIN32
# include <signal.h>
#endif

#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/event_compat.h>
#include <event2/event_struct.h>

#include <event2/dns.h>
#include <event2/dns_compat.h>

#include "ight_wrappers.h"

#include "net/ll2sock.h"

#include "common/poller.h"
#include "common/utils.h"
#include "common/log.h"

struct IghtPoller {
#ifndef WIN32
	struct event evsignal;    /* for SIGINT */
#endif
	struct event_base *base;
	struct evdns_base *dnsbase;
};

struct IghtEvent {
	ight_hook_vo callback;
	ight_hook_vo timeback;
	struct event ev;
	struct timeval tv;
	evutil_socket_t fileno;
	void *opaque;
};

/*
 * IghtEvent implementation
 */

static void
IghtEvent_noop(void *opaque)
{
	(void) opaque;

	/* nothing */ ;
}

static void
IghtEvent_dispatch(evutil_socket_t socket, short event, void *opaque)
{
	struct IghtEvent *nevp;

	(void) socket;

	nevp = (struct IghtEvent *) opaque;
	if (event & EV_TIMEOUT)
		nevp->timeback(nevp->opaque);
	else
		nevp->callback(nevp->opaque);
	free(nevp);
}

static inline struct IghtEvent *
IghtEvent_construct(struct IghtPoller *poller, long long fileno,
    ight_hook_vo callback, ight_hook_vo timeback, void *opaque,
    double timeout, short event)
{
	struct IghtEvent *nevp;
	struct timeval *tvp;
	int result;

	(void) poller;

	nevp = NULL;

	/*
	 * Make sure that, if we want to do I/O, the socket is
	 * valid; otherwise, if we want to do timeout, make sure
	 * that the socket is invalid; while there, catch the
	 * case in which the user passes us an unexpected event.
	 */
	switch (event) {
	case EV_READ:
	case EV_WRITE:
		if (!ight_socket_valid(fileno))
			goto cleanup;
		break;
	case EV_TIMEOUT:
		if (fileno != IGHT_SOCKET_INVALID)
			goto cleanup;
		break;
	default:
		abort();
	}

	if (callback == NULL)
		callback = IghtEvent_noop;
	if (timeback == NULL)
		timeback = IghtEvent_noop;

	nevp = calloc(1, sizeof (*nevp));
	if (nevp == NULL)
		goto cleanup;

	/*
	 * Note: `long long` simplifies the interaction with Java and
	 * shall be wide enough to hold evutil_socket_t, which is `int`
	 * on Unix and `uintptr_t` on Windows.
	 */
	nevp->fileno = (evutil_socket_t) fileno;
	nevp->callback = callback;
	nevp->timeback = timeback;
	nevp->opaque = opaque;

	event_set(&nevp->ev, nevp->fileno, event, IghtEvent_dispatch, nevp);

	tvp = ight_timeval_init(&nevp->tv, timeout);

	result = event_add(&nevp->ev, tvp);
	if (result != 0)
		goto cleanup;

	return (nevp);

      cleanup:
	ight_xfree(nevp);
	return (NULL);
}

/*
 * IghtPoller implementation
 */

#ifndef WIN32
static void
IghtPoller_sigint(int signo, short event, void *opaque)
{
	struct IghtPoller *self;

	(void) signo;
	(void) event;

	self = (struct IghtPoller *) opaque;
	IghtPoller_break_loop(self);
}
#endif

struct IghtPoller *
IghtPoller_construct(void)
{
	struct IghtPoller *self;
	struct event_base *base;
	int retval;

	base = event_init();
	if (base == NULL)
		return (NULL);

	if (evdns_init() != 0)
		return (NULL);

	self = (struct IghtPoller *) calloc(1, sizeof(*self));
	if (self == NULL)
		return (NULL);

	self->base = base;
	self->dnsbase = evdns_get_global_base();
	if (self->dnsbase == NULL)
		abort();

#ifndef WIN32
	event_set(&self->evsignal, SIGINT, EV_SIGNAL,
	    IghtPoller_sigint, self);

	retval = event_add(&self->evsignal, NULL);
	if (retval != 0)
		goto failure;
#endif

	return (self);

      failure:
#ifndef WIN32
	event_del(&self->evsignal);
#endif
	free(self);
	return (NULL);
}

/* Method that we use only internally: */
struct event_base *
IghtPoller_event_base_(struct IghtPoller *self)
{
	return (self->base);
}

/* Method that we use only internally: */
struct evdns_base *
IghtPoller_evdns_base_(struct IghtPoller *self)
{
	return (self->dnsbase);
}

/*
 * This is implemented like in Neubot; however, it is a bit dangerous
 * and/or annoying that one cannot destroy pending callbacks.
 */
int
IghtPoller_sched(struct IghtPoller *self, double delta,
    ight_hook_vo callback, void *opaque)
{
	struct IghtEvent *nevp;

	nevp = IghtEvent_construct(self, IGHT_SOCKET_INVALID,
	    IghtEvent_noop, callback, opaque, delta, EV_TIMEOUT);
	if (nevp == NULL)
		return (-1);
	return (0);
}

void
IghtPoller_loop(struct IghtPoller *self)
{
	(void) self;

	event_dispatch();
}

void
IghtPoller_break_loop(struct IghtPoller *self)
{
	(void) self;

	event_loopbreak();
}
