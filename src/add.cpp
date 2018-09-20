#include "faiss_server.h"

grpc::Status FaissServer::Add(grpc::ServerContext* context,
                              const AddRequest* request,
                              ::google::protobuf::Empty* response) {
  auto vector = request->vector();
  auto vector_size = vector.float_val_size();

  if (vector_size != index_->d) {
    logger_->error("Given vector is invalid size: expect={}, actual={}",
                   index_->d, vector_size);
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Given vector is invalid size");
  }

  auto std_vector =
      std::vector<float>(vector.float_val().begin(), vector.float_val().end());
  logger_->info("Add: size={}", vector_size);

  try {
    index_->add(1, std_vector.data());
  } catch (std::exception& e) {
    logger_->error("Failed to add index: {}", e.what());
    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to add index");
  }

  return grpc::Status::OK;
}
