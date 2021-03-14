from fenics import *
import math


T = 30.0           # final time
num_steps = 75     # number of time steps
dt = T / num_steps # time step size
alpha = 3          # parameter alpha
beta = 0.1         # parameter beta

# Create mesh and define function space
nx = 8
ny = 8
mesh = UnitSquareMesh(nx, ny)
V = FunctionSpace(mesh, 'P', 1)

# Scaled variables
# L = 1; W = 0.2
# mu = 1
# rho = 1
# delta = W/L
# gamma = 0.4*delta**2
# beta = 1.25
# lambda_ = beta
# g = gamma

# Create mesh and define function space
# mesh = BoxMesh(Point(0, 0, 0), Point(L, W, W), 10, 3, 3)
# V = FunctionSpace(mesh, 'P', 1)


# Define boundary condition
# u_D = Expression('1 + x[0]*x[0] + alpha*x[1]*x[1] + beta*t', degree=2, alpha=alpha, beta=beta, t=0)

# u_D = Expression('exp(x[0] + x[1]) * atan2(x[1], x[0]) * (atan2(x[0], x[1])) * (atan2(x[0], x[1])) + beta*t', degree=2, alpha=alpha, beta=beta, t=0)

# u_D = Expression('exp(-((1-x[0])*(1-x[0]) + (1-x[1])*(1-x[1])) / 10) + exp(-((7-x[0])*(7-x[0]) + (7-x[1])*(7-x[1])) / 10) + beta * t', degree=2, beta=beta, t=0)
u_D = Expression('exp(-((4-x[0])*(4-x[0]) + (4-x[1])*(4-x[1])) / 10) + beta * t', degree=2, beta=beta, t=0)


def boundary(x, on_boundary):
    return on_boundary

bc = DirichletBC(V, u_D, boundary)

# Define initial value
u_n = interpolate(u_D, V)
#u_n = project(u_D, V)

# Define variational problem
u = TrialFunction(V)
v = TestFunction(V)
f = Constant(beta - 2 - 2*alpha)
g = Expression("sin(x[0])", degree=2)

# F = u*v*dx + dt*dot(grad(u), grad(v))*dx - (u_n + dt*f)*v*dx  # ???

F = u*v*dx - (u_n + dt*f)*v*dx + inner(grad(u), grad(v)) * dx - 100 * g * v * dx - dt*dot(grad(u), grad(v))*dx

a, L = lhs(F), rhs(F)

res_file = File('coheat/solution.pvd')

# Time-stepping
u = Function(V)
t = 0
for n in range(num_steps):

    # Update current time
    t += dt
    u_D.t = t


    # Compute solution
    solve(a == L, u, bc)


    # Save solution to VTK
    res_file << u

    # Update previous solution
    u_n.assign(u)
