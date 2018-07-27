#include "service_impl.h"

grpc::Status FaissServiceImpl::Search(grpc::ServerContext* context,
                                      const SearchRequest* request,
                                      SearchResponse* response) {
  return grpc::Status::OK;
}

grpc::Status FaissServiceImpl::InternalSearch(
    grpc::ServerContext* context, const InternalSearchRequest* request,
    InternalSearchResponse* response) {
  return grpc::Status::OK;
}