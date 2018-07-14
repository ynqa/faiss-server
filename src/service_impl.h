#ifndef FAISS_SERVER_SERVICE_IMPL_H_
#define FAISS_SERVER_SERVICE_IMPL_H_

#include <grpc++/grpc++.h>
#include "faiss.grpc.pb.h"

using faiss::FaissService;
using faiss::HealthCheckRequest;
using faiss::HealthCheckResponse;

class FaissServiceImpl final : public FaissService::Service {
    public:
        grpc::Status HealthCheck(
            grpc::ServerContext* context,
            const HealthCheckRequest* request,
            HealthCheckResponse* response) override;
};

#endif // FAISS_SERVER_SERVICE_IMPL_H_