#pragma once
#include "IChatModel.h"

class DummyChatModel : public IChatModel {
public:
    std::string getResponse(const std::string& input,
                            const std::vector<Message>& history) const override;
};
