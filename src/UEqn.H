dimensionedScalar UDiffCoef = 4. * delta * Pr.value() / (3. * epsilon.value());
dimensionedScalar velDimUnit(dimVelocity, 1.);

volScalarField oneEpsUBy2 = 1 + 0.5 * epsilon * U;
// surfaceScalarField phiOneEpsUBy2("phiOneEpsUBy2", velDimUnit * linearInterpolate(oneEpsUBy2) * mesh.Sf() & vector(1, 0, 0));
surfaceScalarField phiOneEpsUBy2("phiOneEpsUBy2", velDimUnit 
                                                * fvc::interpolate(oneEpsUBy2, linearInterpolate(U) * mesh.Sf() & vector(1, 0, 0), "reconstruct(oneEpsUBy2)") 
                                                * mesh.Sf() & vector(1, 0, 0));

volScalarField epsTBy2 = 0.5 * epsilon * T;
surfaceScalarField phiEpsTBy2("phiEpsTBy2", velDimUnit * linearInterpolate(epsTBy2) * mesh.Sf() & vector(1, 0, 0));
// surfaceScalarField phiEpsTBy2("phiEpsTBy2", velDimUnit 
//                               * fvc::interpolate(epsTBy2, linearInterpolate(U) * mesh.Sf() & vector(1, 0, 0), "reconstruct(epsTBy2)") 
//                               * mesh.Sf() & vector(1, 0, 0));

fvScalarMatrix pEqn
(
    fvm::ddt(U)
  + fvm::div(phiOneEpsUBy2,U)
  + fvc::div(phiEpsTBy2)
  - fvm::laplacian(UDiffCoef,U)
);

pEqn.solve();
