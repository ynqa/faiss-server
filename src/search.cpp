#include "faiss_server.h"

grpc::Status FaissServer::Search(grpc::ServerContext* context,
                                      const SearchRequest* request,
                                      SearchResponse* response) {
  auto top_k = request->top_k();
  if (top_k <= 0) {
    top_k = default_top_k_;
  }

  if (!request->has_vector()) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Not found vector in request");
  }

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
  logger_->info("Search: top_k={}, size={}", top_k, vector_size);

  std::vector<long> indices(top_k);
  std::vector<float> dist(top_k);

  try {
    index_->search(1, std_vector.data(), top_k, dist.data(), indices.data());
  } catch (std::exception& e) {
    logger_->error("Failed to search index: {}", e.what());
    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to search index");
  }

  for (int i = 0; i < top_k; i++) {
    auto neighbor = response->add_neighbors();
    neighbor->set_id(indices[i]);
    neighbor->set_score(dist[i]);
  }

  return grpc::Status::OK;
}

grpc::Status FaissServer::SearchById(grpc::ServerContext* context,
                                          const SearchByIdRequest* request,
                                          SearchByIdResponse* response) {
  auto top_k = request->top_k();
  if (top_k <= 0) {
    top_k = default_top_k_;
  }

  auto request_id = request->id();
  logger_->info("SearchById: top_k={}, request_id={}", top_k, request_id);

  std::vector<float> request_vector(index_->d);

  try {
    index_->reconstruct(request_id, request_vector.data());
  } catch (std::exception& e) {
    logger_->error("Failed to reconstruct for request id: {}", e.what());
    return grpc::Status(grpc::StatusCode::INTERNAL,
                        "Failed to reconstruct for request id");
  }

  // exclude request id
  top_k++;

  std::vector<long> indices(top_k);
  std::vector<float> dist(top_k);

  try {
    index_->search(1, request_vector.data(), top_k, dist.data(),
                   indices.data());
  } catch (std::exception& e) {
    logger_->error("Failed to search index: {}", e.what());
    return grpc::Status(grpc::StatusCode::INTERNAL, "Failed to search index");
  }

  for (int i = 1; i < top_k; i++) {
    auto neighbor = response->add_neighbors();
    neighbor->set_id(indices[i]);
    neighbor->set_score(dist[i]);
  }

  return grpc::Status::OK;
}
