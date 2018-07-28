#include "service_impl.h"

grpc::Status FaissServiceImpl::Search(grpc::ServerContext* context,
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
  if (vector.float_val_size() != index_->d) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                        "Given vector is invalid size");
  }

  auto std_vector =
      std::vector<float>(vector.float_val().begin(), vector.float_val().end());
  auto std_vector_size = std_vector.size();
  logger_->info("Search: top_k={}, size={}", top_k, std_vector_size);

  std::vector<long> indices(top_k);
  std::vector<float> dist(top_k);

  try {
    index_->search(1, std_vector.data(), top_k, dist.data(), indices.data());
  } catch (std::exception& e) {
    logger_->error("Failed to read index: {}", e.what());
  }

  for (int i = 0; i < top_k; i++) {
    auto neighbor = response->add_neighbors();
    neighbor->set_id(indices[i]);
    neighbor->set_score(dist[i]);
  }

  return grpc::Status::OK;
}

grpc::Status FaissServiceImpl::InternalSearch(
    grpc::ServerContext* context, const InternalSearchRequest* request,
    InternalSearchResponse* response) {
  logger_->info("InternalSearch");
  return grpc::Status::OK;
}