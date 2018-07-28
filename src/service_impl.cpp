#include <faiss/FaissException.h>

#include "service_impl.h"

FaissServiceImpl::FaissServiceImpl(const std::shared_ptr<logger>& logger,
                                   const char* file_path)
    : logger_(logger) {
  try {
    index_ = faiss::read_index(file_path);
  } catch (faiss::FaissException& fe) {
    logger_->error("Failed to read index: {0}", fe.msg);
    std::exit(1);
  } catch (std::exception& e) {
    logger_->error("Failed to read index: {0}", e.what());
    std::exit(1);
  }
}

grpc::Status FaissServiceImpl::HealthCheck(grpc::ServerContext* context,
                                           const HealthCheckRequest* request,
                                           HealthCheckResponse* response) {
  logger_->info("HealthCheck");
  response->set_message("OK");
  return grpc::Status::OK;
}
