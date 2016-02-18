---- Part_2-5.lua
-- Part 2 - Problem 5: Three-of-a-crime
-- Group #4

---- Libraries

require("iuplua")

---- Program Functions

function default()
  iup.Message("Warning", "Not implemented yet")

  return iup.DEFAULT
end

function close()
  return iup.CLOSE
end

function new_game()
  console.append = "New Game Initializing...\n"

  -- Reset Variables
  num_of_players = 1
  players_out = Set({})
  perpetrators = Set({})
  turns_count = 1
  current_criminals = Set({})

  set_players_inactive()

  -- Set number of players
  num_of_players = iup.Alarm("Number of Players", "Select the number of players","One" ,"Two" ,"Three")

  -- Assign three perpetrators
  for i = 1, 3 do
    perpetrator = ""
    repeat
      perpetrator = criminals[math.random(1, 7)]
    until (perpetrators[perpetrator] == nil)
	perpetrators[perpetrator] = true
  end

  -- First turn
  console.append = "New Game Initialized.\n"
  turn()
end

function set_players_active()
  if num_of_players == 3 then
    btn1.active = players_out[1] ~= true and "YES" or "NO"
	btn2.active = players_out[2] ~= true and "YES" or "NO"
	btn3.active = players_out[3] ~= true and "YES" or "NO"
  elseif num_of_players == 2 then
    btn1.active = players_out[1] ~= true and "YES" or "NO"
	btn2.active = players_out[2] ~= true and "YES" or "NO"
	btn3.active = "NO"
  else -- num_of_players == 1
    btn1.active = players_out[1] ~= true and "YES" or "NO"
	btn2.active = "NO"
	btn3.active = "NO"
  end
end

function set_players_inactive()
  btn1.active = "NO"
  btn2.active = "NO"
  btn3.active = "NO"
end

function turn()
  console.append = "Turn " .. turns_count .. ":\n"
  set_players_inactive()
  btn_next.active = "NO"

  -- Reset Turn Variables
  current_perpetrators_count = 0
  current_criminals = Set({})

  -- Assign three criminals, but not three perpetrators
  repeat
    current_perpetrators_count = 0
	current_criminals = Set({})
    for i = 1, 3 do
      local criminal = ""
      repeat
        criminal = criminals[math.random(1, 7)]
      until (current_criminals[criminal] == nil)
	  current_criminals[criminal] = true
	  if perpetrators[criminal] then
	    current_perpetrators_count = current_perpetrators_count + 1
	  end
    end
  until (current_perpetrators_count < 3)

  console.append = "Of the criminals " .. Set_toString(current_criminals) .. ", " .. current_perpetrators_count .. (current_perpetrators_count ~= 1 and " are perpetrators.\n" or " is a perpetrator.\n") ..
                   "Click your respective button if you wish to guess. If not, then click Next.\n"

  set_players_active()
  btn_next.active = "YES"
  turns_count = turns_count + 1
end

function player_guess(player)
  local player_guess = {0,0,0,0,0,0,0}
  local guess_type = iup.ListDialog(2, "Perpetrators (Hold Ctrl)", 7, {"A" ,"B" ,"C", "D", "E", "F", "G"}, 0, 5, 6, player_guess)
  local guess = {}

  -- Convert list of selections to list of criminals
  local cnt = 0
  for i = 1, 7 do
    if player_guess[i] == 1 then
	  cnt = cnt + 1
	  guess[cnt] = criminals[i]
	end
  end

  if guess_type ~= -1 then
    local guess_confirm = iup.Alarm("Confirm Perpetrators", "You guessed: " .. list_toString(guess) .. "\nAre you sure?", "Yes", "No")
	if guess_confirm == 1 then
	  if perpetrators[guess[1]] and perpetrators[guess[2]] and perpetrators[guess[3]] and cnt == 3 then
		player_win(player) -- A player has won!
	  else
		player_out(player) -- A player is out and cannot guess anymore.
	  end
	end
  end
end

function player_win(player)
  iup.Message("Congratulations",
    "You answered correctly!\n" ..
	"Player " .. player .. " wins!")
  console.append = "Congratulations Player " .. player .. "! You were correct!\n"
  set_game_over()
end

function player_out(player)
  iup.Message("Sorry",
    "You answered incorrectly!\n" ..
	"Player " .. player .. " is out!")
  console.append = "Sorry Player " .. player .. "! You are out! Other players may continue.\n"
  players_out[player] = true
  check_end_game()
end

function check_end_game()
  if (num_of_players == 3 and players_out[1] and players_out[2] and players_out[3]) or (num_of_players == 2 and players_out[1] and players_out[2]) or (num_of_players == 1 and players_out[1]) then
    console.append = "All players are out! Game over.\n" ..
	                 "The perpetrators were " .. Set_toString(perpetrators) .. "\n"
	set_game_over()
  else
    set_players_active()
  end
end

function set_game_over()
  set_players_inactive()
  btn_next.active = "NO"
  console.append = "Click Game -> New Game to begin a new game, if desired.\n"
end

function debug_game()
  iup.Message("Debug", -- Will keep debug information when turning in
    "Number of Players: " .. num_of_players .. "\n" ..
	"Criminals: " .. list_toString(criminals) .. "\n" ..
    "Perpetrators: " .. Set_toString(perpetrators) .. "\n" ..
	"Current Criminals: " .. Set_toString(current_criminals) .. "\n" ..
	"Current Perpetrators Count: " .. current_perpetrators_count)
  return iup.DEFAULT
end

function show_instructions()
  iup.Message("Instructions", -- From the prompt
    "Three-of-a-crime is a simple logic game for up to 3 players. There are 7 different criminals. The computer " ..
	"randomly  chooses  three  of  these  (the  \"perpetrators\"),  but  doesn't  tell  the  players  which  are  chosen.  The " ..
	"computer then puts down three random criminals. 0, 1, or 2 of these may be the actual perpetrators. The " ..
	"computer also tells the player how many (but not which) of the three criminals are perpetrators. The players " ..
	"may either guess which three criminals are the actual perpetrators or they may pass. If a player guesses " ..
	"wrong, she is out of the game and the other players continue. If no player chooses to guess, the computer " ..
	"puts down another three randomly chosen criminals (0, 1, or 2 of which may be actual perpetrators) " ..
	"and tells the players how many (but not which) of these are actual perpetrators. Players can again use logic to " ..
	"deduce the three actual criminals and may guess. Play continues until some player guesses correctly or until all players have guessed incorrectly.")
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

function Set(list)
  local set = {}

  for _, l in ipairs(list) do
    set[l] = true
  end

  return set
end

function Set_toString(set)
  local str = "{"

  for l, _ in pairs(set) do
    str = str .. l .. ", "
  end

  return str ~= "{" and str:sub(0, -3) .. "}" or "{}"
end

function list_toString(list)
  local str = "{"

  for _, l in ipairs(list) do
    str = str .. l .. ", "
  end

  return str ~= "{" and str:sub(0, -3) .. "}" or "{}"
end

function splash_screen()
  iup.Message("Three-of-a-crime",
    "Part 2 - Common Programs #5\n" ..
    "Three-of-a-crime\n" ..
	"Team #4\n" ..
	"\n" ..
	"Click OK to begin")
end

---- Init Variables

mmenu = {
  "Game", {
    "New Game", new_game,
	"-", nil,
	"Debug", debug_game,
	"Exit", close
  },
  "Help", {
    "Instructions", show_instructions,
    "About", splash_screen
  }
}
num_of_players = 1
players_out = Set({})
criminals = {"A", "B", "C", "D", "E", "F", "G"}
criminals_set = Set(criminals)
perpetrators = Set({})
turns_count = 1
current_criminals = Set({})
current_perpetrators_count = 0

---- Begin Program

splash_screen()

math.randomseed(os.time())
math.random(); math.random(); math.random() -- Pop a few off random generator

---- Create GUI

-- Textbox - Read Only
console = iup.text({
  expand = "YES",
  readonly = "YES",
  bgcolor = "232 232 232",
  font = "Courier, 11",
  appendnewline = "NO",
  multiline = "YES"
})

-- Buttons
btn1 = iup.button({
  title = "Player 1",
  active = "NO"
})
function btn1:action()
  player_guess(1)
end

btn2 = iup.button({
  title = "Player 2",
  active = "NO"
  })
function btn2:action()
  player_guess(2)
end

btn3 = iup.button({
  title = "Player 3",
  active = "NO"
})
function btn3:action()
  player_guess(3)
end

btn_next = iup.button({
  title = "Next",
  active = "NO"
})
function btn_next:action()
  turn()
end

-- Diablog Boxes
button_box = iup.hbox({
  btn1, btn2, btn3, btn_next;
  gap = 4,
  expand = "NO"
})
box = iup.vbox({
  console, button_box;
  alignment = "ACENTER"
})

-- Main Dialog
dlg = iup.dialog({
  box;
  title = "Three-of-a-crime",
  menu = create_menu(mmenu),
  size = "600x125"
})

-- Show Dialog
dlg:showxy(iup.CENTER, iup.CENTER)

console.append = "Greetings! Please click Game -> New Game to start or Help -> Instructions to see the prompt!\n" ..
                 "The basics: There are seven criminals. Three are the perpetrators. Each turn, the computer will\n" ..
				 "show three ciminals and tell you how many are perpetrators. \n" ..
				 "Click your button to guess, but remember, you only have one guess per player!\n" ..
				 "Hint: When making your guess, hold the Ctrl/Command/etc. key to select more than one criminal.\n"

iup.MainLoop()
