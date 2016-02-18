---- Calculator.lua
-- Part 3 - Advanced Program - Calculator
-- Group #4

---- Libraries
require("iuplua")

---- Program Functions

require("lib/gui/functions")

require("lib/functions")

---- Begin Program

splash_screen()

math.randomseed(os.time())
math.random(); math.random(); math.random() -- Pop a few off random generator

require("lib/gui/main")

require("lib/calculator")

iup.MainLoop()
