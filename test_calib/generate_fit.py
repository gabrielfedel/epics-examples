import numpy as np
fit = []
coef = [ 4.93849614e-01,  4.75739746e+03,  3.30769938e-03, -2.92189409e-05 ]
for i in range(244):
    raw = (i/244)*0.1215
    fit.append(np.polyval(coef, raw))

print(fit)
