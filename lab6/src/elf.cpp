#include "../include/elf.hpp"
#include "../include/druid.hpp"
#include "../include/knight.hpp"

Elf::Elf(int x, int y) : NPC(ElfType, x, y) {}
Elf::Elf(std::istream &is) : NPC(ElfType, is) {}

void Elf::print()
{
    std::cout << *this;
}

void Elf::save(std::ostream &os)
{
    os << ElfType << std::endl;
    NPC::save(os);
}

bool Elf::is_Elf() const
{
    return true;
}

bool Elf::fight(std::shared_ptr<Druid> other)
{
    fight_notify(other, true);
    return true;
}

bool Elf::fight(std::shared_ptr<Knight> other)
{
    fight_notify(other, true);
    return true;
}

bool Elf::fight(std::shared_ptr<Elf> other)
{
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, Elf &knight)
{
    os << "black knight: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}