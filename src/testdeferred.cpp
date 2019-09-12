#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/system.hpp>
#include <eosiolib/transaction.hpp>

using namespace eosio;

class [[eosio::contract("testdeferred")]] testdeferred : public contract {
  public:
      using contract::contract;

[[eosio::action]]
void callupdate(eosio::name from, eosio::name payer, uint64_t id, uint64_t delay)
{
     setupdate(from, payer, id, delay);
}

[[eosio::action]]
void setupdate(eosio::name from, eosio::name payer, uint64_t id, uint64_t delay)
{
     eosio::transaction t{};
     t.actions.emplace_back(
          eosio::permission_level(_self, "active"_n),
          _self,
          "setupdate"_n,
          std::make_tuple(from, payer, id, delay));
     t.delay_sec = delay;
     t.send(now(), _self, true);
}
};


EOSIO_DISPATCH( testdeferred, (setupdate)(callupdate))
