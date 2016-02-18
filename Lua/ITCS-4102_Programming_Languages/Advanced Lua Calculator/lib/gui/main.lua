---- Create GUI

-- Menu
mmenu = {
  "Calculator", {
    "Clear Output", clear_output,
    "Clear Input", clear_input,
    "-", nil,
    "Show Steps", toggle_steps,
	  "Exit", close
  },
  "Functions", {
    "Trig", {
      "sin(x) -> Float", function()
        input_append("sin(")
      end,
      "cos(x) -> Float", function()
        input_append("cos(")
      end,
      "tan(x) -> Float", function()
        input_append("tan(")
      end,
      "sinh(x) -> Float", function()
        input_append("sinh(")
      end,
      "cosh(x) -> Float", function()
        input_append("cosh(")
      end,
      "tanh(x) -> Float", function()
        input_append("tanh(")
      end
    },
    "-", nil,
    "Integer", {
      "floor(x) -> Int", function()
        input_append("floor(")
      end,
      "ceil(x) -> Int", function()
        input_append("ceil(")
      end,
      "round(x) -> Int", function()
        input_append("round(")
      end,
      "gcd(x, y) -> Int", function()
        input_append("gcd(")
      end,
      "factorial(n) -> Int", function()
        input_append("fact(")
      end,
      "fibonacci(n) -> Int", function()
        input_append("fib(")
      end,
      "prime_factorization(x) -> String", function()
        input_append("p_factor(")
      end
    },
    "Real", {
      "min(x, y) -> x/y", function()
        input_append("min(")
      end,
      "max(x, y) -> x/y", function()
        input_append("max(")
      end
    },
    "Logical", {
      "prime(x) -> Bool", function()
        input_append("prime(")
      end,
      "and(x, y) -> Bool", function()
        input_append("and_(")
      end,
      "or(x, y) -> Bool", function()
        input_append("or_(")
      end,
      "equals(x, y) -> Bool", function()
        input_append("equals(")
      end,
      "less_than(x, y) -> Bool", function()
        input_append("l_t(")
      end,
      "greater_than(x, y) -> Bool", function()
        input_append("g_t(")
      end,
      "greater_than_or_equal(x, y) -> Bool", function()
        input_append("g_t_e(")
      end,
      "less_than_or_equal(x, y) -> Bool", function()
        input_append("l_t_r(")
      end
    },
    "-", nil,
    "Memory", {
      "set_memory(x, y) -> Void", function()
        input_append("set_mem(")
      end,
      --"get_memory(x) -> y", function()
      --  input_append("get_mem(")
      --end,
      --"unset_memory(x) -> Void", function()
      --  input_append("unset_mem(")
      --end,
      "reset_memory() -> Void", function()
        input_append("reset_mem()")
      end
    },
    "Misc", {
      "abs(x) -> x", function()
        input_append("abs(")
      end,
      "rand(x, y) -> Int", function()
        input_append("rand(")
      end,
      "rand() -> Float", function()
        input_append("rand()")
      end
    },
    "Conversions", {
      "Decimal_to_Hex(x) -> String", function()
        input_append("d_to_h(")
      end,
      "Hex_to_Decimal(x) -> Float", function()
        input_append("h_to_d(")
      end,
      "Decimal_to_Binary(x) -> String", function()
        input_append("d_to_b(")
      end,
      "Binary_to_Decimal(x) -> Float", function()
        input_append("b_to_d(")
      end
    }
  },
  "Help", {
    "Instructions", show_instructions,
    "Debug", toggle_debug,
    "About", splash_screen
  }
}

-- Textbox - Read Only
Console = {
  current_line = 0,
  memory = {},
  answers = {},
  output = iup.text({
    expand = "YES",
    readonly = "YES",
    bgcolor = "177 177 177",
    font = "Courier new, 11",
    appendnewline = "YES",
    multiline = "YES",
    wordwrap = "YES",
    scrollbar = "VERTICAL",
    canfocus = "NO"
  }),
  input = iup.text({
    expand = "HORIZONTAL",
    readonly = "NO",
    bgcolor = "177 177 177",
    font = "Courier new, 11",
    appendnewline = "NO",
    multiline = "NO"
  }),
  next_line = function()
    if Console.current_line <= #Console.memory then
      Console.input.value = ""
      Console.input.append = Console.memory[Console.current_line + 1]
      Console.current_line = Console.current_line + 1
    end
  end,
  previous_line = function()
    if Console.current_line > 0 then
      Console.input.value = ""
      Console.input.append = Console.memory[Console.current_line - 1]
      Console.current_line = Console.current_line - 1
    end
  end
}

-- Keybinds
function Console.input:k_any(key)
  if (key == iup.K_CR) then  -- Enter key
	  Calculator.run(Console.input.value)
  end
  if (key == iup.K_UP) then  -- Up Arrow
    Console.previous_line()
  end
  if (key == iup.K_DOWN) then  -- Down Arrow
    Console.next_line()
  end
end

-- Buttons
btn = {
  eq = iup.button({
    title = "=",
    rastersize = "50x25",
    active = "YES",
	  action = function()
      Calculator.run()
    end
  }),
  clear = iup.button({
    title = "C",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      Console.input.value = ""
    end
  }),
  zero = iup.button({
    title = "0",
    rastersize = "50x25",
    active = "YES",
	  action = function()
      input_append("0")
    end
  }),
  one = iup.button({
    title = "1",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("1")
    end
  }),
  two = iup.button({
    title = "2",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("2")
    end
  }),
  three = iup.button({
    title = "3",
    rastersize = "25x25",
    active = "YES",
    action = function()
      input_append("3")
    end
  }),
  four = iup.button({
    title = "4",
    rastersize = "25x25",
    active = "YES",
    action = function()
      input_append("4")
    end
  }),
  five = iup.button({
    title = "5",
    rastersize = "25x25",
    active = "YES",
    action = function()
      input_append("5")
    end
  }),
  six = iup.button({
    title = "6",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("6")
    end
  }),
  seven = iup.button({
    title = "7",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("7")
    end
  }),
  eight = iup.button({
    title = "8",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("8")
    end
  }),
  nine = iup.button({
    title = "9",
    rastersize = "25x25",
    active = "YES",
	  action = function()
      input_append("9")
    end
  }),
  period = iup.button({
    title = ".",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append(".")
	  end
  }),
  add = iup.button({
    title = "+",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("+")
	  end
  }),
  minus = iup.button({
    title = "-",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("-")
	  end
  }),
  multiply = iup.button({
    title = "*",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("*")
	  end
  }),
  divide = iup.button({
    title = "/",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("/")
	  end
  }),
  pow = iup.button({
    title = "^",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("^")
	  end
  }),
  sin_ = iup.button({
    title = "sin",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("sin(")
	  end
  }),
  cos_ = iup.button({
    title = "cos",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("cos(")
	  end
  }),
  tan_ = iup.button({
    title = "tan",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("tan(")
	  end
  }),
  parenth_open = iup.button({
    title = "(",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("(")
	  end
  }),
  parenth_close = iup.button({
    title = ")",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append(")")
	  end
  }),
  factorial = iup.button({
    title = "!",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("factorial(")
	  end
  }),
  sqrt_ = iup.button({
    title = "sqrt",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("sqrt(")
	  end
  }),
  modulus = iup.button({
    title = "%",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
      input_append("%")
	  end
  }),
  e_ = iup.button({
    title = "e",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("e")
	  end
  }),
  pi_ = iup.button({
    title = "pi",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("pi")
	  end
  }),
  abs_ = iup.button({
    title = "abs",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("abs(")
	  end
  }),
  i_ = iup.button({
    title = "i",
    rastersize = "25x25",
	  active = "YES",
	  action = function()
	    input_append("i")
	  end
  })
}

-- Diablog Boxes
input_box = iup.hbox({
  Console.input, btn.eq, btn.clear;
})
left_box = iup.vbox({
  Console.output, input_box;
  alignment = "ACENTER"
})

btn_box_7 = iup.vbox({
  btn.pi_, btn.sin_, btn.parenth_open, btn.seven, btn.four, btn.one;
})
btn_box_8 = iup.vbox({
  btn.e_, btn.cos_, btn.parenth_close, btn.eight, btn.five, btn.two;
})
btn_box_9 = iup.vbox({
  btn.i_, btn.tan_, btn.modulus, btn.nine, btn.six, btn.three;
})
btn_box_operands = iup.vbox({
  btn.abs_, btn.sqrt_, btn.pow, btn.divide, btn.multiply, btn.minus, btn.add;
})
btn_box_0 = iup.hbox({
  btn.zero, btn.period;
})
btn_box_nums = iup.hbox({
  btn_box_7, btn_box_8, btn_box_9;
})
btn_box_main = iup.vbox({
  btn_box_nums, btn_box_0;
})

right_box = iup.hbox({
  btn_box_main, btn_box_operands;
})

calculator_box = iup.hbox({
  left_box, right_box;
  alignment = "ABOTTOM",
  gap = "2"
})

-- Main Dialog
dlg = iup.dialog({
  calculator_box;
  title = "Lua Calculator",
  menu = create_menu(mmenu),
  rastersize = "640x250",
  minsize = "640x250"
})

-- Show Dialog
dlg:showxy(iup.CENTER, iup.CENTER)

Console.output.append = default_output()
