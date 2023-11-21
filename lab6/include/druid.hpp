#pragma once
#include "npc.hpp"

struct Druid : public NPC
{
    Druid(int x, int y);
    Druid(std::istream &is);

    void print() override;

    bool is_Druid() const override;

    bool fight(std::shared_ptr<Druid> other) override;
    bool fight(std::shared_ptr<Knight> other) override;
    bool fight(std::shared_ptr<Elf> other) override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Druid &Druid);
};