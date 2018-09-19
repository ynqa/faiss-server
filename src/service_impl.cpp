#include <faiss/FaissException.h>

#include "service_impl.h"

FaissServiceImpl::FaissServiceImpl(const std::shared_ptr<logger>& logger,
                                   const uint& default_top_k,
                                   const char* file_path)
    : logger_(logger), default_top_k_(default_top_k) {
  try {
    index_ = faiss::read_index(file_path);
  } catch (faiss::FaissException& fe) {
    logger_->error("Failed to read index: {}", fe.msg);
    std::exit(1);
  } catch (std::exception& e) {
    logger_->error("Failed to read index: {}", e.what());
    std::exit(1);
  }
}

grpc::Status FaissServiceImpl::HealthCheck(
    grpc::ServerContext* context, const ::google::protobuf::Empty* request,
    HealthCheckResponse* response) {
  logger_->info("HealthCheck");
  response->set_message("OK");
  return grpc::Status::OK;
}
