local custommath = require "custommath"

local a = 1.1
local b = 2.2

print(tostring(a) .. " + " .. tostring(b) .. " = " .. tostring(custommath.add(a, b)))
print(tostring(a) .. " - " .. tostring(b) .. " = " .. tostring(custommath.subtract(a, b)))
print(tostring(a) .. " * " .. tostring(b) .. " = " .. tostring(custommath.multiply(a, b)))
print(tostring(a) .. " / " .. tostring(b) .. " = " .. tostring(custommath.divide(a, b)))
