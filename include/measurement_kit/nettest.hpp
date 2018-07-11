// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_NETTEST_NETTEST_HPP
#define MEASUREMENT_KIT_NETTEST_NETTEST_HPP

/*-
 *  __      __  _____ __________  _______  .___ _______    ________
 * /  \    /  \/  _  \\______   \ \      \ |   |\      \  /  _____/
 * \   \/\/   /  /_\  \|       _/ /   |   \|   |/   |   \/   \  ___
 *  \        /    |    \    |   \/    |    \   /    |    \    \_\  \
 *   \__/\  /\____|__  /____|_  /\____|__  /___\____|__  /\______  /
 *        \/         \/       \/         \/            \/        \/
 *
 * Autogenerated by `./script/autoapi/autoapi`. DO NOT EDIT!!!
 */

#include <assert.h>
#include <stdint.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <measurement_kit/ffi.h>
#include <measurement_kit/common/nlohmann/json.hpp>

namespace mk {
namespace nettest {

// Events
// ------

class FailureAsnLookupEvent {
 public:
  static constexpr const char *key = "failure.asn_lookup";  std::string failure = {}; 
};

class FailureCcLookupEvent {
 public:
  static constexpr const char *key = "failure.cc_lookup";  std::string failure = {}; 
};

class FailureIpLookupEvent {
 public:
  static constexpr const char *key = "failure.ip_lookup";  std::string failure = {}; 
};

class FailureMeasurementEvent {
 public:
  static constexpr const char *key = "failure.measurement";  std::string failure = {}; 
};

class FailureMeasurementSubmissionEvent {
 public:
  static constexpr const char *key = "failure.measurement_submission";  std::string failure = {};  int64_t idx = {};  std::string json_str = {}; 
};

class FailureReportCreateEvent {
 public:
  static constexpr const char *key = "failure.report_create";  std::string failure = {}; 
};

class FailureReportCloseEvent {
 public:
  static constexpr const char *key = "failure.report_close";  std::string failure = {}; 
};

class FailureResolverLookupEvent {
 public:
  static constexpr const char *key = "failure.resolver_lookup";  std::string failure = {}; 
};

class FailureStartupEvent {
 public:
  static constexpr const char *key = "failure.startup";  std::string failure = {}; 
};

class LogEvent {
 public:
  static constexpr const char *key = "log";  std::string log_level = {};  std::string message = {}; 
};

class MeasurementEvent {
 public:
  static constexpr const char *key = "measurement";  int64_t idx = {};  std::string json_str = {}; 
};

class StatusEndEvent {
 public:
  static constexpr const char *key = "status.end";  double downloaded_kb = {};  double uploaded_kb = {};  std::string failure = {}; 
};

class StatusGeoipLookupEvent {
 public:
  static constexpr const char *key = "status.geoip_lookup";  std::string probe_ip = {};  std::string probe_asn = {};  std::string probe_cc = {};  std::string probe_network_name = {}; 
};

class StatusProgressEvent {
 public:
  static constexpr const char *key = "status.progress";  double percentage = {};  std::string message = {}; 
};

class StatusQueuedEvent {
 public:
  static constexpr const char *key = "status.queued"; 
};

class StatusMeasurementStartEvent {
 public:
  static constexpr const char *key = "status.measurement_start";  int64_t idx = {};  std::string input = {}; 
};

class StatusMeasurementSubmissionEvent {
 public:
  static constexpr const char *key = "status.measurement_submission";  int64_t idx = {}; 
};

class StatusMeasurementDoneEvent {
 public:
  static constexpr const char *key = "status.measurement_done";  int64_t idx = {}; 
};

class StatusReportCloseEvent {
 public:
  static constexpr const char *key = "status.report_close";  std::string report_id = {}; 
};

class StatusReportCreateEvent {
 public:
  static constexpr const char *key = "status.report_create";  std::string report_id = {}; 
};

class StatusResolverLookupEvent {
 public:
  static constexpr const char *key = "status.resolver_lookup";  std::string ip_address = {}; 
};

class StatusStartedEvent {
 public:
  static constexpr const char *key = "status.started"; 
};

class StatusUpdatePerformanceEvent {
 public:
  static constexpr const char *key = "status.update.performance";  std::string direction = {};  double elapsed = {};  int64_t num_streams = {};  double speed_kbps = {}; 
};

class StatusUpdateWebsitesEvent {
 public:
  static constexpr const char *key = "status.update.websites";  std::string url = {};  std::string status = {}; 
};

class TaskTerminatedEvent {
 public:
  static constexpr const char *key = "task_terminated"; 
};


// Settings
// --------

class CommonSettings {
 public:
   static constexpr const char *log_level_err = "ERR";  static constexpr const char *log_level_warning = "WARNING";  static constexpr const char *log_level_info = "INFO";  static constexpr const char *log_level_debug = "DEBUG";  static constexpr const char *log_level_debug2 = "DEBUG2"; 

   std::map<std::string, std::string> annotations = {};  std::vector<std::string> disabled_events = {};  std::vector<std::string> inputs = {};  std::vector<std::string> input_filepaths = {};  std::string log_filepath = {};  std::string log_level = log_level_err;  std::string output_filepath = {}; 

   std::string bouncer_base_url = "https://bouncer.ooni.io";  std::string collector_base_url = {};  std::string dns_nameserver = {};  std::string dns_engine = "system";  std::string geoip_asn_path = {};  std::string geoip_country_path = {};  bool ignore_bouncer_error = true;  bool ignore_open_report_error = true;  double max_runtime = -1.0;  std::string net_ca_bundle_path = {};  double net_timeout = 10.0;  bool no_bouncer = false;  bool no_collector = false;  bool no_asn_lookup = false;  bool no_cc_lookup = false;  bool no_ip_lookup = false;  bool no_file_report = false;  bool no_resolver_lookup = false;  std::string probe_asn = {};  std::string probe_cc = {};  std::string probe_ip = {};  bool randomize_input = true;  bool save_real_probe_asn = true;  bool save_real_probe_cc = true;  bool save_real_probe_ip = false;  bool save_real_resolver_ip = true;  std::string software_name = {};  std::string software_version = {}; 
};


class CaptivePortalSettings : public CommonSettings {
 public:
  static constexpr const char *name = "CaptivePortal"; 
  std::string serialize();
};

class DashSettings : public CommonSettings {
 public:
  static constexpr const char *name = "Dash"; 
  std::string serialize();
};

class DnsInjectionSettings : public CommonSettings {
 public:
  static constexpr const char *name = "DnsInjection"; 
  std::string serialize();
};

class FacebookMessengerSettings : public CommonSettings {
 public:
  static constexpr const char *name = "FacebookMessenger"; 
  std::string serialize();
};

class HttpHeaderFieldManipulationSettings : public CommonSettings {
 public:
  static constexpr const char *name = "HttpHeaderFieldManipulation"; 
  std::string serialize();
};

class HttpInvalidRequestLineSettings : public CommonSettings {
 public:
  static constexpr const char *name = "HttpInvalidRequestLine"; 
  std::string serialize();
};

class MeekFrontedRequestsSettings : public CommonSettings {
 public:
  static constexpr const char *name = "MeekFrontedRequests"; 
  std::string serialize();
};

class MultiNdtSettings : public CommonSettings {
 public:
  static constexpr const char *name = "MultiNdt"; 
  std::string serialize();
};

class NdtSettings : public CommonSettings {
 public:
  static constexpr const char *name = "Ndt"; 
  std::string serialize();
};

class TcpConnectSettings : public CommonSettings {
 public:
  static constexpr const char *name = "TcpConnect"; 
  std::string serialize();
};

class TelegramSettings : public CommonSettings {
 public:
  static constexpr const char *name = "Telegram"; 
  std::string serialize();
};

class WebConnectivitySettings : public CommonSettings {
 public:
  static constexpr const char *name = "WebConnectivity"; 
  std::string serialize();
};

class WhatsappSettings : public CommonSettings {
 public:
  static constexpr const char *name = "Whatsapp";  bool all_endpoints = false; 
  std::string serialize();
};


class Runner {
 public:
   virtual void on_failure_asn_lookup(const FailureAsnLookupEvent &);  virtual void on_failure_cc_lookup(const FailureCcLookupEvent &);  virtual void on_failure_ip_lookup(const FailureIpLookupEvent &);  virtual void on_failure_measurement(const FailureMeasurementEvent &);  virtual void on_failure_measurement_submission(const FailureMeasurementSubmissionEvent &);  virtual void on_failure_report_create(const FailureReportCreateEvent &);  virtual void on_failure_report_close(const FailureReportCloseEvent &);  virtual void on_failure_resolver_lookup(const FailureResolverLookupEvent &);  virtual void on_failure_startup(const FailureStartupEvent &);  virtual void on_log(const LogEvent &);  virtual void on_measurement(const MeasurementEvent &);  virtual void on_status_end(const StatusEndEvent &);  virtual void on_status_geoip_lookup(const StatusGeoipLookupEvent &);  virtual void on_status_progress(const StatusProgressEvent &);  virtual void on_status_queued(const StatusQueuedEvent &);  virtual void on_status_measurement_start(const StatusMeasurementStartEvent &);  virtual void on_status_measurement_submission(const StatusMeasurementSubmissionEvent &);  virtual void on_status_measurement_done(const StatusMeasurementDoneEvent &);  virtual void on_status_report_close(const StatusReportCloseEvent &);  virtual void on_status_report_create(const StatusReportCreateEvent &);  virtual void on_status_resolver_lookup(const StatusResolverLookupEvent &);  virtual void on_status_started(const StatusStartedEvent &);  virtual void on_status_update_performance(const StatusUpdatePerformanceEvent &);  virtual void on_status_update_websites(const StatusUpdateWebsitesEvent &);  virtual void on_task_terminated(const TaskTerminatedEvent &); 

  void run(std::string str);

  Runner() noexcept;
  virtual ~Runner() noexcept;
};

/*-
 * __________        .__               __
 * \______   \_______|__|__  _______ _/  |_  ____
 *  |     ___/\_  __ \  \  \/ /\__  \\   __\/ __ \
 *  |    |     |  | \/  |\   /  / __ \|  | \  ___/
 *  |____|     |__|  |__| \_/  (____  /__|  \___  >
 *                                  \/          \/
 *
 * Definitions ends here. What follows is the inline implementation of this
 * API, which you can exclude by setting MK_NETTEST_NO_INLINE_IMPL.
 *
 * This is handy if you want to include this code in many translation
 * units to include the implementation into a single object.
 */
#if !defined MK_NETTEST_NO_INLINE_IMPL && !defined SWIG

// Utility classes
// ---------------

class TaskDeleter {
 public:
  void operator()(mk_task_t *task) noexcept { mk_task_destroy(task); }
};
using UniqueTask = std::unique_ptr<mk_task_t, TaskDeleter>;

class EventDeleter {
 public:
  void operator()(mk_event_t *event) noexcept { mk_event_destroy(event); }
};
using UniqueEvent = std::unique_ptr<mk_event_t, EventDeleter>;

// Empty event handlers
// --------------------

 void Runner::on_failure_asn_lookup(const FailureAsnLookupEvent &) {}  void Runner::on_failure_cc_lookup(const FailureCcLookupEvent &) {}  void Runner::on_failure_ip_lookup(const FailureIpLookupEvent &) {}  void Runner::on_failure_measurement(const FailureMeasurementEvent &) {}  void Runner::on_failure_measurement_submission(const FailureMeasurementSubmissionEvent &) {}  void Runner::on_failure_report_create(const FailureReportCreateEvent &) {}  void Runner::on_failure_report_close(const FailureReportCloseEvent &) {}  void Runner::on_failure_resolver_lookup(const FailureResolverLookupEvent &) {}  void Runner::on_failure_startup(const FailureStartupEvent &) {}  void Runner::on_log(const LogEvent &) {}  void Runner::on_measurement(const MeasurementEvent &) {}  void Runner::on_status_end(const StatusEndEvent &) {}  void Runner::on_status_geoip_lookup(const StatusGeoipLookupEvent &) {}  void Runner::on_status_progress(const StatusProgressEvent &) {}  void Runner::on_status_queued(const StatusQueuedEvent &) {}  void Runner::on_status_measurement_start(const StatusMeasurementStartEvent &) {}  void Runner::on_status_measurement_submission(const StatusMeasurementSubmissionEvent &) {}  void Runner::on_status_measurement_done(const StatusMeasurementDoneEvent &) {}  void Runner::on_status_report_close(const StatusReportCloseEvent &) {}  void Runner::on_status_report_create(const StatusReportCreateEvent &) {}  void Runner::on_status_resolver_lookup(const StatusResolverLookupEvent &) {}  void Runner::on_status_started(const StatusStartedEvent &) {}  void Runner::on_status_update_performance(const StatusUpdatePerformanceEvent &) {}  void Runner::on_status_update_websites(const StatusUpdateWebsitesEvent &) {}  void Runner::on_task_terminated(const TaskTerminatedEvent &) {} 

// Serializers
// -----------

static std::string serialize_common(nlohmann::json &&doc, const CommonSettings &cs) {
  doc["annotations"] = cs.annotations;doc["disabled_events"] = cs.disabled_events;doc["inputs"] = cs.inputs;doc["input_filepaths"] = cs.input_filepaths;doc["log_filepath"] = cs.log_filepath;doc["log_level"] = cs.log_level;doc["output_filepath"] = cs.output_filepath;
  {
    auto &o = doc["options"];
    o["bouncer_base_url"] = cs.bouncer_base_url;o["collector_base_url"] = cs.collector_base_url;o["dns/nameserver"] = cs.dns_nameserver;o["dns/engine"] = cs.dns_engine;o["geoip_asn_path"] = cs.geoip_asn_path;o["geoip_country_path"] = cs.geoip_country_path;o["ignore_bouncer_error"] = (int64_t)cs.ignore_bouncer_error;o["ignore_open_report_error"] = (int64_t)cs.ignore_open_report_error;o["max_runtime"] = cs.max_runtime;o["net/ca_bundle_path"] = cs.net_ca_bundle_path;o["net/timeout"] = cs.net_timeout;o["no_bouncer"] = (int64_t)cs.no_bouncer;o["no_collector"] = (int64_t)cs.no_collector;o["no_asn_lookup"] = (int64_t)cs.no_asn_lookup;o["no_cc_lookup"] = (int64_t)cs.no_cc_lookup;o["no_ip_lookup"] = (int64_t)cs.no_ip_lookup;o["no_file_report"] = (int64_t)cs.no_file_report;o["no_resolver_lookup"] = (int64_t)cs.no_resolver_lookup;o["probe_asn"] = cs.probe_asn;o["probe_cc"] = cs.probe_cc;o["probe_ip"] = cs.probe_ip;o["randomize_input"] = (int64_t)cs.randomize_input;o["save_real_probe_asn"] = (int64_t)cs.save_real_probe_asn;o["save_real_probe_cc"] = (int64_t)cs.save_real_probe_cc;o["save_real_probe_ip"] = (int64_t)cs.save_real_probe_ip;o["save_real_resolver_ip"] = (int64_t)cs.save_real_resolver_ip;o["software_name"] = cs.software_name;o["software_version"] = cs.software_version;
  }
  return doc.dump();
}


std::string CaptivePortalSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "CaptivePortal";
  return serialize_common(std::move(doc), *this);
}

std::string DashSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "Dash";
  return serialize_common(std::move(doc), *this);
}

std::string DnsInjectionSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "DnsInjection";
  return serialize_common(std::move(doc), *this);
}

std::string FacebookMessengerSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "FacebookMessenger";
  return serialize_common(std::move(doc), *this);
}

std::string HttpHeaderFieldManipulationSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "HttpHeaderFieldManipulation";
  return serialize_common(std::move(doc), *this);
}

std::string HttpInvalidRequestLineSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "HttpInvalidRequestLine";
  return serialize_common(std::move(doc), *this);
}

std::string MeekFrontedRequestsSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "MeekFrontedRequests";
  return serialize_common(std::move(doc), *this);
}

std::string MultiNdtSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "MultiNdt";
  return serialize_common(std::move(doc), *this);
}

std::string NdtSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "Ndt";
  return serialize_common(std::move(doc), *this);
}

std::string TcpConnectSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "TcpConnect";
  return serialize_common(std::move(doc), *this);
}

std::string TelegramSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "Telegram";
  return serialize_common(std::move(doc), *this);
}

std::string WebConnectivitySettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "WebConnectivity";
  return serialize_common(std::move(doc), *this);
}

std::string WhatsappSettings::serialize() {
  nlohmann::json doc;
  doc["name"] = "Whatsapp";doc["options"]["all_endpoints"] = (int64_t)all_endpoints;
  return serialize_common(std::move(doc), *this);
}


void Runner::run(std::string str) {
  UniqueTask task;
#ifdef MK_NETTEST_TRACE
  std::clog << "NETTEST: settings: " << str << std::endl;
#endif
  task.reset(mk_task_start(str.c_str()));
  if (!task) {
    throw std::runtime_error("mk_task_start() failed");
  }
  while (!mk_task_is_done(task.get())) {
    nlohmann::json ev;
    {
      UniqueEvent event{mk_task_wait_for_next_event(task.get())};
      if (!event) {
        throw std::runtime_error("mk_task_wait_for_next_event() failed");
      }
      auto str = mk_event_serialize(event.get());
      if (!str) {
        throw std::runtime_error("mk_event_serialize() failed");
      }
#ifdef MK_NETTEST_TRACE
      std::clog << "NETTEST: event: " << str << std::endl;
#endif
      ev = nlohmann::json::parse(str);
    }

    
    if (ev.at("key") == FailureAsnLookupEvent::key) {
      FailureAsnLookupEvent event; event.failure = ev.at("value").at("failure");
      on_failure_asn_lookup(event);
      continue;
    }
    
    if (ev.at("key") == FailureCcLookupEvent::key) {
      FailureCcLookupEvent event; event.failure = ev.at("value").at("failure");
      on_failure_cc_lookup(event);
      continue;
    }
    
    if (ev.at("key") == FailureIpLookupEvent::key) {
      FailureIpLookupEvent event; event.failure = ev.at("value").at("failure");
      on_failure_ip_lookup(event);
      continue;
    }
    
    if (ev.at("key") == FailureMeasurementEvent::key) {
      FailureMeasurementEvent event; event.failure = ev.at("value").at("failure");
      on_failure_measurement(event);
      continue;
    }
    
    if (ev.at("key") == FailureMeasurementSubmissionEvent::key) {
      FailureMeasurementSubmissionEvent event; event.failure = ev.at("value").at("failure");event.idx = ev.at("value").at("idx");event.json_str = ev.at("value").at("json_str");
      on_failure_measurement_submission(event);
      continue;
    }
    
    if (ev.at("key") == FailureReportCreateEvent::key) {
      FailureReportCreateEvent event; event.failure = ev.at("value").at("failure");
      on_failure_report_create(event);
      continue;
    }
    
    if (ev.at("key") == FailureReportCloseEvent::key) {
      FailureReportCloseEvent event; event.failure = ev.at("value").at("failure");
      on_failure_report_close(event);
      continue;
    }
    
    if (ev.at("key") == FailureResolverLookupEvent::key) {
      FailureResolverLookupEvent event; event.failure = ev.at("value").at("failure");
      on_failure_resolver_lookup(event);
      continue;
    }
    
    if (ev.at("key") == FailureStartupEvent::key) {
      FailureStartupEvent event; event.failure = ev.at("value").at("failure");
      on_failure_startup(event);
      continue;
    }
    
    if (ev.at("key") == LogEvent::key) {
      LogEvent event; event.log_level = ev.at("value").at("log_level");event.message = ev.at("value").at("message");
      on_log(event);
      continue;
    }
    
    if (ev.at("key") == MeasurementEvent::key) {
      MeasurementEvent event; event.idx = ev.at("value").at("idx");event.json_str = ev.at("value").at("json_str");
      on_measurement(event);
      continue;
    }
    
    if (ev.at("key") == StatusEndEvent::key) {
      StatusEndEvent event; event.downloaded_kb = ev.at("value").at("downloaded_kb");event.uploaded_kb = ev.at("value").at("uploaded_kb");event.failure = ev.at("value").at("failure");
      on_status_end(event);
      continue;
    }
    
    if (ev.at("key") == StatusGeoipLookupEvent::key) {
      StatusGeoipLookupEvent event; event.probe_ip = ev.at("value").at("probe_ip");event.probe_asn = ev.at("value").at("probe_asn");event.probe_cc = ev.at("value").at("probe_cc");event.probe_network_name = ev.at("value").at("probe_network_name");
      on_status_geoip_lookup(event);
      continue;
    }
    
    if (ev.at("key") == StatusProgressEvent::key) {
      StatusProgressEvent event; event.percentage = ev.at("value").at("percentage");event.message = ev.at("value").at("message");
      on_status_progress(event);
      continue;
    }
    
    if (ev.at("key") == StatusQueuedEvent::key) {
      StatusQueuedEvent event; 
      on_status_queued(event);
      continue;
    }
    
    if (ev.at("key") == StatusMeasurementStartEvent::key) {
      StatusMeasurementStartEvent event; event.idx = ev.at("value").at("idx");event.input = ev.at("value").at("input");
      on_status_measurement_start(event);
      continue;
    }
    
    if (ev.at("key") == StatusMeasurementSubmissionEvent::key) {
      StatusMeasurementSubmissionEvent event; event.idx = ev.at("value").at("idx");
      on_status_measurement_submission(event);
      continue;
    }
    
    if (ev.at("key") == StatusMeasurementDoneEvent::key) {
      StatusMeasurementDoneEvent event; event.idx = ev.at("value").at("idx");
      on_status_measurement_done(event);
      continue;
    }
    
    if (ev.at("key") == StatusReportCloseEvent::key) {
      StatusReportCloseEvent event; event.report_id = ev.at("value").at("report_id");
      on_status_report_close(event);
      continue;
    }
    
    if (ev.at("key") == StatusReportCreateEvent::key) {
      StatusReportCreateEvent event; event.report_id = ev.at("value").at("report_id");
      on_status_report_create(event);
      continue;
    }
    
    if (ev.at("key") == StatusResolverLookupEvent::key) {
      StatusResolverLookupEvent event; event.ip_address = ev.at("value").at("ip_address");
      on_status_resolver_lookup(event);
      continue;
    }
    
    if (ev.at("key") == StatusStartedEvent::key) {
      StatusStartedEvent event; 
      on_status_started(event);
      continue;
    }
    
    if (ev.at("key") == StatusUpdatePerformanceEvent::key) {
      StatusUpdatePerformanceEvent event; event.direction = ev.at("value").at("direction");event.elapsed = ev.at("value").at("elapsed");event.num_streams = ev.at("value").at("num_streams");event.speed_kbps = ev.at("value").at("speed_kbps");
      on_status_update_performance(event);
      continue;
    }
    
    if (ev.at("key") == StatusUpdateWebsitesEvent::key) {
      StatusUpdateWebsitesEvent event; event.url = ev.at("value").at("url");event.status = ev.at("value").at("status");
      on_status_update_websites(event);
      continue;
    }
    
    if (ev.at("key") == TaskTerminatedEvent::key) {
      TaskTerminatedEvent event; 
      on_task_terminated(event);
      continue;
    }
    

#ifdef MK_NETTEST_TRACE
      std::clog << "NETTEST: unhandled event: " << str << std::endl;
#endif
  }
}

// Misc
// ----

Runner::Runner() noexcept {}

Runner::~Runner() noexcept {}

#endif  // !MK_NETTEST_NO_INLINE_IMPL && !SWIG
}  // namespace nettest
}  // namespace mk
#endif  // MEASUREMENT_KIT_NETTEST_HPP