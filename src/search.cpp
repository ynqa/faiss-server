#include "service_impl.h"

grpc::Status FaissServiceImpl::Search(grpc::ServerContext* context,
                                      const SearchRequest* request,
                                      SearchResponse* response) {
  logger_->info("Search: top_k {0}", request->top_k());
  auto vector = std::vector<float>(request->vector().float_val().begin(),
                                   request->vector().float_val().end());
  return grpc::Status::OK;
}

grpc::Status FaissServiceImpl::InternalSearch(
    grpc::ServerContext* context, const InternalSearchRequest* request,
    InternalSearchResponse* response) {
  logger_->info("InternalSearch");
  return grpc::Status::OK;
}