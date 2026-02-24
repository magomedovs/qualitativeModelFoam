/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2025 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    qualitativeModelFoam

Description
    Transient solver for toy model system for flames and detonations.

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "timeSelector.H"
#include "pimpleControl.H"

#include "fvcDdt.H"
#include "fvcGrad.H"
#include "fvcSnGrad.H"
#include "fvcFlux.H"

#include "fvmDdt.H"
#include "fvmDiv.H"
#include "fvmLaplacian.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"

    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (pimple.loop(runTime))
    {
        Info<< "\n Time = " << runTime.name() << nl << endl;

        // #include "CourantNo.H"

        while (pimple.loop())
        {
            #include "UEqn.H"

            // Oleg's code
            // volScalarField reactionRate = k*exp(-rho*E/p);
            // solve
            // (
            //     fvm::ddt(rhoLambda)
            // + fvc::div(phiLambdap)
            // ==
            //     rho*reactionRate - fvm::Sp(reactionRate, rhoLambda)
            // );

            volScalarField reactionRate = k * exp(-theta / T) * pos(T - T_ign);
            omega = (1. - Y) * reactionRate;
            #include "TEqn.H"
            #include "YEqn.H"
        }

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
