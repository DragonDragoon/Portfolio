-- Global require
local lpeg = require("lpeg")

-- Functions
function tree_node(p)
  return p / function(left, mid, right)
    if mid == nil then
	  return left
	elseif type(left) == "string" and string.len(left) > 2 then
	  if right ~= nil then
	    if Settings.isDebugging then
	      print("{" .. tostring(left) .. "," .. tostring(mid) .. "," .. tostring(right) .. "}")
		end
		return { left, mid, right }
	  elseif mid ~= nil then
		if Settings.isDebugging then
	      print("{" .. tostring(left) .. "," .. tostring(mid) .. "}")
		end
	    return { left, mid }
	  else
		if Settings.isDebugging then
	      print("{" .. tostring(left) .. "}")
		end
	    return { left }
	  end
	else
	  if Settings.isDebugging then
	    print("{" .. tostring(mid) .. "," .. tostring(left) .. "," .. tostring(right) .. "}")
	  end
      return { mid, left, right }
	end
  end
end

-- Grammar
local space = lpeg.S(" \n\t")^0
local add_sub_op = lpeg.C(lpeg.S("+-")) * space
local mul_div_op = lpeg.C(lpeg.S("*/%")) * space
local pow_op = lpeg.C(lpeg.P("^")) * space
local par_open = "(" * space
local par_close = ")" * space
local negative = lpeg.P("-")
local period = lpeg.P(".")
local comma = lpeg.P(",") * space
local zero_to_nine = lpeg.R("09")
local a_to_Z = lpeg.R("az", "AZ")
local underscore = lpeg.P("_")

Grammar = lpeg.P({ "Expression",
  Expression = tree_node(lpeg.V("Term") * lpeg.Cg(add_sub_op * lpeg.V("Expression"))^0);
  Term = tree_node(lpeg.V("Factor") * lpeg.Cg(mul_div_op * lpeg.V("Term"))^0);
  Factor = tree_node(lpeg.V("Bracket") * lpeg.Cg(pow_op * lpeg.V("Factor"))^0);
  Bracket = tree_node(lpeg.V("Word")^-1 * par_open * lpeg.V("Expression") * (comma * lpeg.V("Expression"))^-1 * par_close + lpeg.V("Number") + lpeg.V("Word"));
  Word = lpeg.C(lpeg.V("Letter")^1) * space / tostring;
  Letter = a_to_Z + underscore;
  Number = lpeg.C(negative^-1 * lpeg.V("Digit")^1 * (period^-1 * lpeg.V("Digit")^1)^0) * space / tonumber;
  Digit = zero_to_nine;
})

-- Settings
Settings = {
  isDebugging = false,
  showingSteps = false
}

-- Evaluator
Evaluator = {
  steps_string = "",
  final = "",
  run = function(ast)
    if type(ast) == "table" then
	  if Settings.showingSteps then
	    Evaluator.final = tostring(Evaluator.evaluate_subtree(ast))
		return ""
	  else
	    Evaluator.final = tostring(Evaluator.evaluate_subtree(ast))
        return "  " .. Evaluator.final .. "\n"
	  end
	elseif type(ast) == "number" then
	  Evaluator.final = ast
	  return "  " .. ast .. "\n"
	elseif type(ast) == "string" then
	  Evaluator.final = ast
	  return "  " .. tostring(Evaluator.evaluate_word(ast)) .. "\n"
    end
  end,
  evaluate_subtree = function(ast)
    if type(ast) == "number" then
	  return ast
	elseif type(ast) == "string" then
	  return Evaluator.evaluate_word(ast)
	elseif type(ast[1]) == "string" and string.len(ast[1]) > 2 then
	  local func = ast[1]
	  local argu = tostring(Evaluator.evaluate_subtree(ast[2])) .. ((ast[3] ~= nil) and ", " .. tostring(Evaluator.evaluate_subtree(ast[3])) or "")
	  if Settings.isDebugging then
	    print("  " .. func .. "(" .. argu .. ")" .. "=" .. tostring(Evaluator.evaluate_function(func, argu)))
	  end
	  if Settings.showingSteps then
	    Evaluator.steps_string = Evaluator.steps_string .. "  -> " .. tostring(func) .. "(" .. tostring(argu) .. ")" .. " = " .. tostring(Evaluator.evaluate_function(func, argu)) .. "\n"
	  end
	  return Evaluator.evaluate_function(func, argu)
	else
	  local op = ast[1]
	  local left = Evaluator.evaluate_subtree(ast[2])
	  local right = Evaluator.evaluate_subtree(ast[3])
	  if Settings.isDebugging then
	    print("  " .. tostring(left) .. tostring(op) .. tostring(right) .. "=" .. tostring(Evaluator.evaluate(op, tonumber(left), tonumber(right))))
	  end
	  if Settings.showingSteps then
	    Evaluator.steps_string = Evaluator.steps_string .. "  -> " .. tostring(left) .. " " .. tostring(op) .. " " .. tostring(right) .. " = " .. tostring(Evaluator.evaluate(op, left, right)) .. "\n"
	  end
	  return Evaluator.evaluate(op, tonumber(left), tonumber(right))
	end
  end,
  to_string = function(ast)
    if type(ast) == "number" or type(ast) == "string" then
	  return ast
	elseif #ast == 2 then
	  local func = ast[1]
	  local argu = Evaluator.to_string(ast[2])
	  return "{" .. tostring(func) .. ", " .. tostring(argu) .. "}"
	else
	  if type(ast[1]) == "string" and string.len(ast[1]) > 2 then
        local func = ast[1]
	    local arg1 = Evaluator.to_string(ast[2])
	    local arg2 = Evaluator.to_string(ast[3])
	    return "{" .. tostring(func) .. ", " .. tostring(arg1) .. ", " .. tostring(arg2) .. "}"
	  else
	    local op = ast[1]
	    local left = Evaluator.to_string(ast[2])
	    local right = Evaluator.to_string(ast[3])
	    return "{" .. tostring(op) .. ", " .. tostring(left) .. ", " .. tostring(right) .. "}"
	  end
	end
  end,
  syntax_to_string = function(ast)
	if type(ast) == "number" or type(ast) == "string" then
	  return ast
	elseif #ast == 2 then
	  local func = ast[1]
	  local argu = Evaluator.syntax_to_string(ast[2])
	  return tostring(func) .. "(" .. tostring(argu) .. ")"
	else
	  if type(ast[1]) == "string" and string.len(ast[1]) > 2 then
        local func = ast[1]
	    local arg1 = Evaluator.syntax_to_string(ast[2])
	    local arg2 = Evaluator.syntax_to_string(ast[3])
	    return tostring(func) .. "(" .. tostring(arg1) .. ", " .. tostring(arg2) .. ")"
	  else
	    local op = ast[1]
	    local left = Evaluator.syntax_to_string(ast[2])
	    local right = Evaluator.syntax_to_string(ast[3])
	    return "(" .. tostring(left) .. " " .. tostring(op) .. " " .. tostring(right) .. ")"
	  end
	end
  end,
  evaluate = function(op, left, right)
    if op == "+" then
	  return Calculator.add(left, right)
	elseif op == "-" then
	  return Calculator.subtract(left, right)
	elseif op == "*" then
	  return Calculator.multiply(left, right)
	elseif op == "/" then
	  return Calculator.divide(left, right)
	elseif op == "^" then
	  return Calculator.pow(left, right)
	elseif op == "%" then
	  return Calculator.modulus(left, right)
	else
	  return Evaluator.exception("Unknown operator: " .. tostring(op))
	end
  end,
  evaluate_function = function(func, argu)
    local arguments = {}
    for value in string.gmatch(argu, '([^,]+)') do
	  value = value:match("^%s*(.-)%s*$")
      table.insert(arguments, value)
    end
	if #arguments == 0 then
	  if func == "test" then
	    return "test()"
	  else
	    return func .. "()"
	  end
	elseif #arguments == 1 then
	  arg1 = arguments[1]
	  if func == "test" then
	    return "test(" .. arg1 .. ")"
      elseif func == "sqrt" then
	    return Calculator.sqrt_(arg1)
	  elseif func == "sin" then
	    return Calculator.sin_(arg1)
	  elseif func == "cos" then
	    return Calculator.cos_(arg1)
	  elseif func == "tan" then
	    return Calculator.tan_(arg1)
	  elseif func == "sinh" then
	    return Calculator.sinh_(arg1)
	  elseif func == "cosh" then
	    return Calculator.cosh_(arg1)
	  elseif func == "tanh" then
	    return Calculator.tanh_(arg1)
	  elseif func == "abs" then
	    return Calculator.abs_(arg1)
	  elseif func == "round" then
	    return Calculator.round(arg1)
	  elseif func == "ceil" then
	    return Calculator.ceil_(arg1)
	  elseif func == "floor" then
	    return Calculator.floor_(arg1)
	  elseif func == "prev" then
	    return Calculator.previous(arg1)
	  elseif func == "p_factor" then
	    return Calculator.prime_factorization(arg1)
	  elseif func == "eval" then
	    return Calculator.eval(arg1)
	  elseif func == "prime" then
	    return Calculator.prime(arg1)
	  elseif func == "d_to_h" then
	    return Calculator.decimal_to_hex_(arg1)
	  elseif func == "h_to_d" then
	    return Calculator.hex_to_decimal_(arg1)
	  elseif func == "d_to_b" then
	    return Calculator.decimal_to_binary_(arg1)
	  elseif func == "b_to_d" then
	    return Calculator.binary_to_decimal_(arg1)
	  elseif func == "fib" then
	    return Calculator.fib_(arg1)
	  elseif func == "fact" then
	    return Calculator.factorial_(arg1)
	  --elseif func == "get_mem" then
	  --  return Calculator.get_mem(arg1)
	  --elseif func == "unset_mem" then
	  --  return Calculator.unset_mem(arg1)
	  else
	    return func .. "(" .. argu .. ")"
	  end
	elseif #arguments == 2 then
	  arg1 = arguments[1]
	  arg2 = arguments[2]
	  if func == "test" then
	    return "test(" .. arg1 .. ", " .. arg2 .. ")"
	  elseif func == "and_" then
	    return Calculator.and_(arg1, arg2)
	  elseif func == "or_" then
	    return Calculator.or_(arg1, arg2)
	  elseif func == "equals" then
	    return Calculator.equals_(arg1, arg2)
	  elseif func == "l_t" then
	    return Calculator.less_than(arg1, arg2)
	  elseif func == "g_t" then
	    return Calculator.greater_than(arg1, arg2)
	  elseif func == "g_t_e" then
	    return Calculator.greater_than_or_equals(arg1, arg2)
	  elseif func == "l_t_e" then
	    return Calculator.less_than_or_equals(arg1, arg2)
	  elseif func == "rand" then
	    return Calculator.rand(arg1, arg2)
	  elseif func == "set_mem" then
	    return Calculator.set_mem(arg1, arg2)
	  elseif func == "max" then
	    return Calculator.max_(arg1, arg2)
	  elseif func == "min" then
	    return Calculator.min_(arg1, arg2)
	  elseif func == "gcd" then
	    return Calculator.gcd_(arg1, arg2)
	  else
	    return func .. "(" .. arg1 .. ", " .. arg2 .. ")"
	  end
	else
	  return Evaluator.exception("Too many arguments in function: " .. func)
	end
  end,
  evaluate_word = function(word)
    if word == "test" then
	  return "test"
    elseif word == "pi" then
	  return math.pi
	elseif word == "e" then
	  return 2.7182818284590
	elseif word == "mx" then
	  return math.huge
	elseif word == "i" then
	  return math.sqrt(-1)
	elseif word == "true" then
	  return true
	elseif word == "false" then
	  return false
	elseif word == "reset_mem" then
	  return Calculator.reset_mem()
	elseif word == "rand" then
	  return Calculator.rand()
	elseif Calculator.memory[word] ~= nil then
	  return Calculator.memory[word]
	else
	  return word
	end
  end,
  exception = function(str)
    return "Error: invalid expression " .. ((str ~= nil) and "(" .. str .. ")" or "")
  end
}

-- Calculator
Calculator = {
  memory = {},
  run = function(str)
    if Console ~= nil then
	  str = Console.input.value:match("^%s*(.-)%s*$")
	  if Settings.isDebugging then
	    print("Debug:\n  Syntax tree: " .. Evaluator.to_string(Grammar:match(str)) .. "\n  Steps:\n")
	  end
	  local eval_string = Evaluator.run(Grammar:match(str))
      Console.output.append = str .. " ->\n"
	                              .. "  " .. Evaluator.syntax_to_string(Grammar:match(str)) .. " =\n"
								  .. ((Settings.isDebugging) and "  -> " .. Evaluator.to_string(Grammar:match(str)) .. "\n" or "")
								  .. eval_string .. Evaluator.steps_string
	  table.insert(Console.memory, Console.input.value)
	  local trimmed_string = Evaluator.final
	  if Settings.isDebugging then
	    print("Trimmed final: " .. trimmed_string)
	  end
	  table.insert(Console.memory, trimmed_string)
	  table.insert(Console.answers, trimmed_string)
	  Console.current_line = #Console.memory + 1
      --Console.input.value = ""
	  Evaluator.steps_string = ""
	else
	  str = str:match("^%s*(.-)%s*$")
	  if Settings.isDebugging then
        print(Evaluator.run(Grammar:match(str)))
	  end
	end
  end,
  add = function(left, right)
    return left + right
  end,
  subtract = function(left, right)
    return left - right
  end,
  multiply = function(left, right)
    return left * right
  end,
  divide = function(left, right)
    return left / right
  end,
  pow = function(left, right)
    return left ^ right
  end,
  modulus = function(left, right)
    return left % right
  end,
  sqrt_ = function(arg1)
    return math.sqrt(arg1)
  end,
  sin_ = function(arg1)
    return math.sin(arg1)
  end,
  cos_ = function(arg1)
    return math.cos(arg1)
  end,
  tan_ = function(arg1)
    return math.tan(arg1)
  end,
  sinh_ = function(arg1)
    return math.sinh(arg1)
  end,
  cosh_ = function(arg1)
    return math.cosh(arg1)
  end,
  tanh_ = function(arg1)
    return math.tanh(arg1)
  end,
  abs_ = function(arg1)
    return math.abs(arg1)
  end,
  round = function(arg1)
	if arg1 % 2 ~= 0.5 then
      return math.floor(arg1 + 0.5)
    end
      return arg1 - 0.5
  end,
  prime = function(arg1)
    local n = tonumber(arg1)
    for i = 2, n^(1/2) do
      if (n % i) == 0 then
	    return false
	  end
    end
	return true
  end,
  prime_factorization = function(arg1)
	local i = 2
    local factors = {}
	local num = tonumber(arg1)
    if not num or num < 1 then
        return false
    end
    if num and num == 1 then
	  return false
    end
    while num and num > 1 do
	  while num % i == 0 do
	    factors[#factors + 1] = i
	    num = num / i
	  end
	  i = i + 1
    end
    return Calculator.prime_factorization_tostring(factors)
  end,
  prime_factorization_tostring = function(t)
    local str = ""
    for k, v in pairs(t) do
      str = str .. v .. ' * '
    end
	return str:match("^(.-)%s*\*%s*$")
  end,
  eval = function(arg1)
    return Evaluator.run(Grammar:match(arg1))
  end,
  ceil_ = function(arg1)
    return math.ceil(arg1)
  end,
  floor_ = function(arg1)
    return math.floor(arg1)
  end,
  previous = function(argu)
    return Console.answers[#Console.answers - tonumber(argu) + 1]
  end,
  set_mem = function(arg1, arg2)
    Calculator.memory[arg1] = arg2
    return arg1 .. " -> " .. arg2 .. "\n  Success"
  end,
  get_mem = function(arg1)
    return Calculator.memory[arg1]
  end,
  unset_mem = function(arg1)
    Calculator.memory[arg1] = arg1
	return arg1 .. " -> " .. arg1 .. "\n  Success"
  end,
  reset_mem = function()
    Calculator.memory = {}
	return "Clear Memory\n  Success"
  end,
  and_ = function(arg1, arg2)
    return (arg1 == "true") and (arg2 == "true")
  end,
  or_ = function(arg1, arg2)
    return (arg1 == "true") or (arg2 == "true")
  end,
  equals_ = function(arg1, arg2)
    return tonumber(arg1) == tonumber(arg2)
  end,
  less_than_or_equals = function(arg1, arg2)
    return tonumber(arg1) <= tonumber(arg2)
  end,
  less_than = function(arg1, arg2)
    return tonumber(arg1) < tonumber(arg2)
  end,
  greater_than_or_equals = function(arg1, arg2)
    return tonumber(arg1) >= tonumber(arg2)
  end,
  greater_than = function(arg1, arg2)
    return tonumber(arg1) > tonumber(arg2)
  end,
  rand = function(arg1, arg2)
    return (arg1 ~= nil and arg2 ~= nil) and math.random(arg1, arg2) or math.random()
  end,
  max_ = function(x,y)
	local isNumber = (tonumber(x) and tonumber(y)) and true or false
	if isNumber then
	  return math.max(x,y)
	else
	  return Evaluator.exception("max(x, y): One or both inputs are not numbers.")
	end
  end,
  min_ = function(x,y)
	local isNumber = (tonumber(x) and tonumber(y)) and true or false
	if isNumber then
	  return math.min(x,y)
	else
	  return Evaluator.exception("min(x, y): One or both inputs are not numbers.")
	end
  end,
  gcd_ = function(x,y)
	local isNumber = (tonumber(x) and tonumber(y)) and true or false
	if isNumber then
	  local temp = nil
	  while x ~= 0 do
	    temp = x
		x = math.mod(y, x)
		y = temp
	  end
	  return y
	else
	  return Evaluator.exception("gcd(x, y): One or both inputs are not numbers.")
	end
  end,
  hex_to_decimal_ = function(input)
	local decimalOutput = (input ~= nil) and tonumber(input, 16) or false
	if decimalOutput then
		return decimalOutput
	else
		return Evaluator.exception("h_to_d(x): Input is not hexadecimal.")
	end
  end,
  decimal_to_hex_ = function(input)
	local isNumber = (input~=nil) and tonumber(input) or false
	if isNumber  then
	  local isDecimal = (math.floor(isNumber) == isNumber) and isNumber or false
	  if isDecimal then
		return string.format("%X", isDecimal)
	  else
		return Evaluator.exception("d_to_h(x): Input is not a decimal.")
	  end
	else
	  return Evaluator.exception("d_to_h(x): Input is not a number.")
	end
  end,
  binary_to_decimal_ = function(input)
	local integerOutput = (input ~= nil) and tonumber(input, 2) or false
	if integerOutput then
	  return integerOutput
	else
	  return Evaluator.exception("b_to_d(x): Input is not binary.")
	end
  end,
  decimal_to_binary_ = function(input)
	local isNumber = (input~=nil) and tonumber(input) or false
	if isNumber then
	  local isDecimal = (math.floor(isNumber) == isNumber) and isNumber or false
	  if isDecimal then
		local binaryOutput = ""
        while isDecimal > 0 do
		  local dividedInput = isDecimal / 2
		  local moddedWhole, remainderFraction = math.modf(dividedInput)
		  binaryOutput = math.ceil(remainderFraction) .. binaryOutput
		  isDecimal = moddedWhole
	    end
          return binaryOutput
	  else
		return Evalutor.exception("d_to_b(x): Input is not a decimal.")
	  end
	else
	  return Evaluator.exception("d_to_b(x): Input is not a number.")
	end
  end,
  fib_ = function(arg1)
    local fibs = {1, 1}
	local n = tonumber(arg1)
    for i = 3, n do
      fibs[i] = fibs[i - 1] + fibs[i - 2]
	  if Settings.showingSteps then
	    Evaluator.steps_string = Evaluator.steps_string .. "  -> " .. fibs[i - 1] .. " + " .. fibs[i - 2] .. " = " .. fibs[i] .. "\n"
	  end
    end
    return fibs[n]
  end,
  factorial_ = function(arg1)
    local facts = {1}
	local n = tonumber(arg1)
    for i = 2, n do
      facts[i] = i * facts[i - 1]
	  if Settings.showingSteps then
	    Evaluator.steps_string = Evaluator.steps_string .. "  -> " .. i .. " * " .. facts[i - 1] .. " = " .. facts[i] .. "\n"
	  end
    end
    return facts[n]
  end
}
