// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/common/version.h>
#include <openssl/opensslv.h>
#include <event2/event.h>

const char *mk_version() {
    return MK_VERSION;
}

const char *mk_version_with_git_tag() {
    return MK_VERSION_WITH_GIT_TAG;
}

const char *mk_openssl_version() {
    return OPENSSL_VERSION_TEXT;
}

const char *mk_libevent_version() {
    return LIBEVENT_VERSION;
}
