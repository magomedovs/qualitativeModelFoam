
fvScalarMatrix TEqn
(
    fvm::ddt(T)
  - fvc::ddt(U)
  ==
    q*omega
  + fvm::laplacian(delta, T)
);

TEqn.solve();
