#include "service_impl.h"

grpc::Status FaissServiceImpl::HealthCheck(grpc::ServerContext* context,
                                           const HealthCheckRequest* request,
                                           HealthCheckResponse* response) {
  console_->info("HealthCheck");
  response->set_message("OK");
  return grpc::Status::OK;
}
