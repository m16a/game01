#pragma once

#ifndef _UNIT_H_
#define _UNIT_H_

namespace model {
    class Unit {
    private:
        long long id;
        int x;
        int y;
    protected:
        Unit(long long id, int x, int y);
    public:
        virtual ~Unit();

        long long getId() const;
        int getX() const;
        int getY() const;

        double getDistanceTo(int x, int y) const;
        double getDistanceTo(const Unit& unit) const;
    };
}

#endif
