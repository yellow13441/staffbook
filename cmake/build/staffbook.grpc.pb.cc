// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: staffbook.proto

#include "staffbook.pb.h"
#include "staffbook.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace staffbook {

static const char* CURD_method_names[] = {
  "/staffbook.CURD/AddEmployee",
  "/staffbook.CURD/ListEmployees",
  "/staffbook.CURD/QueryEmployeeByID",
};

std::unique_ptr< CURD::Stub> CURD::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< CURD::Stub> stub(new CURD::Stub(channel, options));
  return stub;
}

CURD::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_AddEmployee_(CURD_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListEmployees_(CURD_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_QueryEmployeeByID_(CURD_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status CURD::Stub::AddEmployee(::grpc::ClientContext* context, const ::staffbook::Employee& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::staffbook::Employee, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddEmployee_, context, request, response);
}

void CURD::Stub::async::AddEmployee(::grpc::ClientContext* context, const ::staffbook::Employee* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::staffbook::Employee, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddEmployee_, context, request, response, std::move(f));
}

void CURD::Stub::async::AddEmployee(::grpc::ClientContext* context, const ::staffbook::Employee* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddEmployee_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CURD::Stub::PrepareAsyncAddEmployeeRaw(::grpc::ClientContext* context, const ::staffbook::Employee& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::staffbook::Employee, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddEmployee_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* CURD::Stub::AsyncAddEmployeeRaw(::grpc::ClientContext* context, const ::staffbook::Employee& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddEmployeeRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CURD::Stub::ListEmployees(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::staffbook::StaffBook* response) {
  return ::grpc::internal::BlockingUnaryCall< ::google::protobuf::Empty, ::staffbook::StaffBook, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_ListEmployees_, context, request, response);
}

void CURD::Stub::async::ListEmployees(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::staffbook::StaffBook* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::google::protobuf::Empty, ::staffbook::StaffBook, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListEmployees_, context, request, response, std::move(f));
}

void CURD::Stub::async::ListEmployees(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::staffbook::StaffBook* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_ListEmployees_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::staffbook::StaffBook>* CURD::Stub::PrepareAsyncListEmployeesRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::staffbook::StaffBook, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_ListEmployees_, context, request);
}

::grpc::ClientAsyncResponseReader< ::staffbook::StaffBook>* CURD::Stub::AsyncListEmployeesRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncListEmployeesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status CURD::Stub::QueryEmployeeByID(::grpc::ClientContext* context, const ::staffbook::IDRequest& request, ::staffbook::Employee* response) {
  return ::grpc::internal::BlockingUnaryCall< ::staffbook::IDRequest, ::staffbook::Employee, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_QueryEmployeeByID_, context, request, response);
}

void CURD::Stub::async::QueryEmployeeByID(::grpc::ClientContext* context, const ::staffbook::IDRequest* request, ::staffbook::Employee* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::staffbook::IDRequest, ::staffbook::Employee, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_QueryEmployeeByID_, context, request, response, std::move(f));
}

void CURD::Stub::async::QueryEmployeeByID(::grpc::ClientContext* context, const ::staffbook::IDRequest* request, ::staffbook::Employee* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_QueryEmployeeByID_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::staffbook::Employee>* CURD::Stub::PrepareAsyncQueryEmployeeByIDRaw(::grpc::ClientContext* context, const ::staffbook::IDRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::staffbook::Employee, ::staffbook::IDRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_QueryEmployeeByID_, context, request);
}

::grpc::ClientAsyncResponseReader< ::staffbook::Employee>* CURD::Stub::AsyncQueryEmployeeByIDRaw(::grpc::ClientContext* context, const ::staffbook::IDRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncQueryEmployeeByIDRaw(context, request, cq);
  result->StartCall();
  return result;
}

CURD::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CURD_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CURD::Service, ::staffbook::Employee, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CURD::Service* service,
             ::grpc::ServerContext* ctx,
             const ::staffbook::Employee* req,
             ::google::protobuf::Empty* resp) {
               return service->AddEmployee(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CURD_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CURD::Service, ::google::protobuf::Empty, ::staffbook::StaffBook, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CURD::Service* service,
             ::grpc::ServerContext* ctx,
             const ::google::protobuf::Empty* req,
             ::staffbook::StaffBook* resp) {
               return service->ListEmployees(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      CURD_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< CURD::Service, ::staffbook::IDRequest, ::staffbook::Employee, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](CURD::Service* service,
             ::grpc::ServerContext* ctx,
             const ::staffbook::IDRequest* req,
             ::staffbook::Employee* resp) {
               return service->QueryEmployeeByID(ctx, req, resp);
             }, this)));
}

CURD::Service::~Service() {
}

::grpc::Status CURD::Service::AddEmployee(::grpc::ServerContext* context, const ::staffbook::Employee* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CURD::Service::ListEmployees(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::staffbook::StaffBook* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status CURD::Service::QueryEmployeeByID(::grpc::ServerContext* context, const ::staffbook::IDRequest* request, ::staffbook::Employee* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace staffbook

