#include "../include/druid.hpp"
#include "../include/knight.hpp"
#include "../include/elf.hpp"

Druid::Druid(int x, int y) : NPC(DruidType, x, y) {}
Druid::Druid(std::istream &is) : NPC(DruidType, is) {}

void Druid::print()
{
    std::cout << *this;
}

bool Druid::is_Druid() const 
{
    return true;
}

bool Druid::fight(std::shared_ptr<Druid> other) 
{
    fight_notify(other, false);
    return false;
}

bool Druid::fight(std::shared_ptr<Knight> other) 
{
    fight_notify(other, false);
    return false;
}

bool Druid::fight(std::shared_ptr<Elf> other) 
{
    fight_notify(other, false);
    return false;
}

void Druid::save(std::ostream &os) 
{
    os << DruidType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Druid &Druid)
{
    os << "Druid: " << *static_cast<NPC *>(&Druid) << std::endl;
    return os;
}