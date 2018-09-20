#include <faiss/FaissException.h>

#include "faiss_server.h"

FaissServer::FaissServer(const std::shared_ptr<logger>& logger,
                         const uint& default_top_k, const char* file_path)
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

grpc::Status FaissServer::Heartbeat(grpc::ServerContext* context,
                                    const ::google::protobuf::Empty* request,
                                    HeartbeatResponse* response) {
  logger_->info("Heartbeat");
  response->set_message("OK");
  return grpc::Status::OK;
}
