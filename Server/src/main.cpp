#include <iostream>

#include "Common/Message/MessageType.hpp"
#include "Server/ProcessUnit/Acceptor.hpp"

int main(int _ac, const char ** _av)
{
    {
        fix::msg::Logon logon{};
        logon.Header.set<fix::Tag::BeginString>("begin");
        logon.Header.set<fix::Tag::BodyLength>("len");
        logon.Header.set<fix::Tag::SenderCompId>("send");
        logon.Header.set<fix::Tag::TargetCompId>("target");
        logon.Header.set<fix::Tag::MsgSeqNum>("seq");
        logon.Header.set<fix::Tag::SendingTime>("time");
        auto tuple = logon.list<fix::Tag::NoMDEntries>().newTags();
        fix::com::get<fix::Tag::MDEntryType>(tuple) = "type";
        fix::com::get<fix::Tag::MDEntryPx>(tuple) = "30.00";
        fix::com::get<fix::Tag::MDEntrySize>(tuple) = std::nullopt;
        logon.list<fix::Tag::NoMDEntries>().add(tuple);
        logon.set<fix::Tag::EncryptMethod>("aze");
        logon.set<fix::Tag::HearBtInt>("12");
        std::cout << logon.to_string() << std::endl;
        std::cout << logon.Header.get<fix::Tag::BeginString>() << std::endl;
        std::optional<std::string> target = logon.Header.get<fix::Tag::TargetCompId>();
        if (target.has_value()) {
            std::cout << "target has value: " << target.value() << std::endl;
        }
        else {
            std::cout << "target has no value" << std::endl;
        }
    }

    asio::io_context asio_ctx{};
    fix::serv::ProcessUnit<fix::serv::pu::Acceptor> acceptor{asio_ctx, 8080};
    fix::serv::ProcessUnit<fix::serv::pu::MessageRouter> router{};

    router.setInput(acceptor.getOutput(fix::serv::pu::Acceptor::OutputName::Message));

    acceptor.run();
    return 0;
}