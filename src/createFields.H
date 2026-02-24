Info<< "Reading field U\n" << endl;

volScalarField U
(
    IOobject
    (
        "U",
        runTime.name(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field T\n" << endl;

volScalarField T
(
    IOobject
    (
        "T",
        runTime.name(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field Y\n" << endl;

volScalarField Y
(
    IOobject
    (
        "Y",
        runTime.name(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading parameters\n" << endl;

IOdictionary parameters
(
    IOobject
    (
        "parameters",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);


dimensionedScalar delta("delta",     dimKinematicViscosity, parameters);
dimensionedScalar epsilon("epsilon", dimless, parameters);
dimensionedScalar Pr("Pr",           dimless, parameters);
dimensionedScalar Le("Le",           dimless, parameters);
dimensionedScalar k("k",             inv(dimTime), parameters);
dimensionedScalar theta("theta",     dimless, parameters);
dimensionedScalar q("q",             dimless, parameters);      
dimensionedScalar T_ign("T_ign",     dimless, parameters); 


Info<< "Creating field omega\n" << endl;

volScalarField omega
(
    IOobject
    (
        "omega",
        runTime.name(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    (1. - Y) * k * exp(-theta / T) * pos(T - T_ign) //T * dimensionedScalar{inv(dimTime), 1.}
);

// Info<< "Calculating field (1 + 0.5 * epsilon * p)\n" << endl;

// volScalarField oneEpsPBy2
// (
//     IOobject
//     (
//         "oneEpsPBy2",
//         runTime.name(),
//         mesh,
//         IOobject::NO_READ,
//         IOobject::AUTO_WRITE
//     ),
//     1 + 0.5 * epsilon * p //mesh,
//     //dimensionedScalar("oneEpsPBy2", dimVelocity, 0.0)
// );

// #include "createPhi.H"

// #include "createFvOptions.H"
