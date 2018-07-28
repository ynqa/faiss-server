#include "service_impl.h"

grpc::Status FaissServiceImpl::Search(grpc::ServerContext* context,
                                      const SearchRequest* request,
                                      SearchResponse* response) {
  logger_->info("Search");
  return grpc::Status::OK;
}

grpc::Status FaissServiceImpl::InternalSearch(
    grpc::ServerContext* context, const InternalSearchRequest* request,
    InternalSearchResponse* response) {
  logger_->info("InternalSearch");
  return grpc::Status::OK;
}