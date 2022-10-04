import ufl

element =  ufl.FiniteElement("P", ufl.triangle, degree=1,quad_scheme='default') #ufl.FiniteElement("Quadrature", ufl.triangle, degree=0,quad_scheme='default')

u = ufl.TrialFunction(element)
v = ufl.TestFunction(element)

#a = u*v*ufl.dx
#a = ufl.inner(ufl.grad(u),ufl.grad(v))*(ufl.dx+ufl.dc)
a = u*v*(ufl.dx+ufl.dc)
#a = u*v*(ufl.dc)
#a = u*v*ufl.dx(metadata={"quadrature_rule":"run_time"})

#forms = [a]
#compiled_forms, module, code = ffcx.codegeneration.jit.compile_forms(forms)
