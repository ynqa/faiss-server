#ifndef FAISS_SERVER_H_
#define FAISS_SERVER_H_

#include <faiss/Index.h>
#include <faiss/index_io.h>
#include <grpc++/grpc++.h>
#include <spdlog/spdlog.h>

#include "protobuf/faiss.grpc.pb.h"

using faiss::AddRequest;
using faiss::FaissService;
using faiss::HeartbeatResponse;
using faiss::SearchByIdRequest;
using faiss::SearchByIdResponse;
using faiss::SearchRequest;
using faiss::SearchResponse;

using spdlog::logger;

class FaissServer final : public FaissService::Service {
 public:
  FaissServer(const std::shared_ptr<logger>& logger, const uint& default_top_k,
              const char* file_path);

  grpc::Status Heartbeat(grpc::ServerContext* context,
                         const ::google::protobuf::Empty* request,
                         HeartbeatResponse* response) override;

  grpc::Status Search(grpc::ServerContext* context,
                      const SearchRequest* request,
                      SearchResponse* response) override;

  grpc::Status SearchById(grpc::ServerContext* context,
                          const faiss::SearchByIdRequest* request,
                          faiss::SearchByIdResponse* response) override;

  grpc::Status Add(grpc::ServerContext* context,
                   const faiss::AddRequest* request,
                   ::google::protobuf::Empty* response) override;

 private:
  const std::shared_ptr<logger>& logger_;
  const uint& default_top_k_;
  faiss::Index* index_;
};

#endif  // FAISS_SERVER_H_
