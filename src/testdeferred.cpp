#pragma once

#include <testdeferred.hpp>


using namespace eosio;

class [[eosio::contract("testdeferred")]] hello : public contract {
  public:
      using contract::contract;

[[eosio::action]]
void setupdate(eosio::name from, eosio::name payer, uint64_t id, uint64_t delay, uint64_t tx_id)
{
     eosio::transaction t{};
     t.actions.emplace_back(
          eosio::permission_level(get_self(), "active"_n),
          get_self(),
          "setupdate"_n,
          std::make_tuple(id));
     t.delay_sec = delay;
     t.send(tx_id, get_self(), true);
}
};
