/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_POINTMOVEMENTGENERATOR_H
#define MANGOS_POINTMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "FollowerReference.h"
#include "Timer.h"
#include "Creature.h"

template<class T>
class MANGOS_DLL_SPEC PointMovementGenerator
: public MovementGeneratorMedium< T, PointMovementGenerator<T> >
{
    public:
        PointMovementGenerator(uint32 _id, float _x, float _y, float _z) : id(_id),
            i_x(_x), i_y(_y), i_z(_z), i_nextMoveTime(0) {}

        void Initialize(T &);
        void Finalize(T &);
        void Interrupt(T &);
        void Reset(T &unit);
        bool Update(T &, const uint32 &diff);

        void MovementInform(T &);

        MovementGeneratorType GetMovementGeneratorType() const { return POINT_MOTION_TYPE; }

        bool GetDestination(float& x, float& y, float& z) const { x=i_x; y=i_y; z=i_z; return true; }
    private:
        uint32 id;
        float i_x,i_y,i_z;
        TimeTracker i_nextMoveTime;
};

class MANGOS_DLL_SPEC AssistanceMovementGenerator
: public PointMovementGenerator<Creature>
{
    public:
        AssistanceMovementGenerator(float _x, float _y, float _z) :
            PointMovementGenerator<Creature>(0, _x, _y, _z) {}

        MovementGeneratorType GetMovementGeneratorType() const { return ASSISTANCE_MOTION_TYPE; }
        void Finalize(Unit &);
};

#endif
