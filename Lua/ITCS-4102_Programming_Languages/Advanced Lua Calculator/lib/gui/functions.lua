function default()
  iup.Message("Warning", "Not implemented yet")
  return iup.DEFAULT
end

function close()
  return iup.CLOSE
end

function create_menu(templ)
  local items = {}

  for i = 1,#templ,2 do
    local label = templ[i]
    local data = templ[i+1]

    if type(data) == 'function' then
      item = iup.item{title = label}
      item.action = data
    elseif type(data) == 'nil' then
      item = iup.separator({})
    else
      item = iup.submenu({create_menu(data); title = label})
    end

    table.insert(items, item)
  end

  return iup.menu(items)
end

function input_append(str)
  Console.input.append = str
end

function toggle_steps()
  if Settings.showingSteps then
    Console.output.append = "Set Showing Steps = false"
    Settings.showingSteps = false
	Console.output.append = "  Success\n"
  else
    Console.output.append = "Set Showing Steps = true"
    Settings.showingSteps = true
	Console.output.append = "  Success\n"
  end
end

function toggle_debug()
  if Settings.isDebugging then
    Console.output.append = "Set Debug Mode = false"
    Settings.isDebugging = false
	Console.output.append = "  Success\n"
  else
    Console.output.append = "Set Debug Mode = true"
    Settings.isDebugging = true
	Console.output.append = "  Success\n"
  end
end

function clear_input()
  Console.input.value = ""
end

function clear_output()
  Console.memory = {}
  Console.answers = {}
  Console.current_line = 0
  Console.output.value = default_output()
end

function default_output()
  return "\n\n\n\n\n\n\n\nGreetings!"
end

function show_instructions()
  iup.Message("Instructions",
    "Operators:\n" ..
    "  + -> Addition -> 1 + 3 = 4\n" ..
    "  - -> Subtraction -> 1 - 3 = -2\n" ..
    "  * -> Multiplication -> 1 * 3 = 3\n" ..
    "  / -> Division -> 1 / 3 = 0.33333333333333\n" ..
    "  % -> Modulus -> 1 % 3 = 1\n" ..
	"  ^ -> Power -> 1 ^ 3 = 1\n" ..
    "Constants:\n" ..
    "  pi -> Pi -> pi = 3.1415926535898\n" ..
    "  e -> Euler's Number -> e = 2.718281828459\n" ..
    "  i -> Complex Number -> i = -1.#IND (Not intended to be used)\n" ..
	"Buttons:\n" ..
	"  C -> Clear -> Clears the console input\n" ..
	"  = -> Evaluate -> Evaluates the given expression in console input\n" ..
	"Keybinds:\n" ..
	"  Enter -> Evaluate -> Evaluates the given expression in the console input\n" ..
	"  Up Arrow -> Previous Output -> Sets the console input to a previous output, from the current output\n" ..
	"  Down Arrow -> Next Output -> Sets the console input to the next output, from the current output\n" ..
	"Helpful Functions:\n" ..
	"  prev(x) -> Previous answer x -> Returns a previous answer\n" ..
	"  mem_set(x, y) -> Bind x to y -> Sets constant x to value y\n" ..
	"  reset_mem() -> Resets all memory constants\n" ..
	"\n")
end

function splash_screen()
  iup.Message("Calculator Info",
    "ITCS-4102 - Project - Part 3 - Advanced Program\n" ..
    "Calculator\n" ..
	"Team #4\n" ..
	"    William Woodard\n" ..
	"    Yuhan Zhang\n" ..
	"    Bryron Ho")
end
