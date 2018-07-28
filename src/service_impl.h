#ifndef FAISS_SERVER_SERVICE_IMPL_H_
#define FAISS_SERVER_SERVICE_IMPL_H_

#include <faiss/index_io.h>
#include <grpc++/grpc++.h>
#include <spdlog/spdlog.h>

#include "faiss.grpc.pb.h"

using faiss::FaissService;
using faiss::HealthCheckRequest;
using faiss::HealthCheckResponse;
using faiss::InternalSearchRequest;
using faiss::InternalSearchResponse;
using faiss::SearchRequest;
using faiss::SearchResponse;

using spdlog::logger;

class FaissServiceImpl final : public FaissService::Service {
 public:
  FaissServiceImpl(const std::shared_ptr<logger>& logger,
                   const char* file_path);

  grpc::Status HealthCheck(grpc::ServerContext* context,
                           const HealthCheckRequest* request,
                           HealthCheckResponse* response) override;

  grpc::Status Search(grpc::ServerContext* context,
                      const SearchRequest* request,
                      SearchResponse* response) override;

  grpc::Status InternalSearch(grpc::ServerContext* context,
                              const faiss::InternalSearchRequest* request,
                              faiss::InternalSearchResponse* response) override;

 private:
  const std::shared_ptr<logger>& logger_;
  faiss::Index* index_;
};

#endif  // FAISS_SERVER_SERVICE_IMPL_H_