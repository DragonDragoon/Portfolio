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
