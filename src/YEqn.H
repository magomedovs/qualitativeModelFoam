
fvScalarMatrix YEqn
(
    fvm::ddt(Y)
  ==
    omega
  + fvm::laplacian(delta/Le, Y)
);

YEqn.solve();
