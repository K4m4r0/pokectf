-- =========================
-- ctf_vendor_unlock.lua
-- Portable version for Windows and Linux
-- =========================

local MAGIC_ADDR  = 0x02000AD2
local MAGIC_VALUE = 0xC7F7

local fired = false

local function joinPath(dir, file)
    if not dir or dir == "" then
        return file
    end

    local last = dir:sub(-1)
    if last == "/" or last == "\\" then
        return dir .. file
    end

    -- Preserve whichever separator the path already seems to use
    if dir:find("\\") then
        return dir .. "\\" .. file
    end

    return dir .. "/" .. file
end

local function getScriptDir()
    -- Newer/development mGBA builds
    if script and script.dir then
        return script.dir
    end

    -- Fallback: derive from Lua's own source path
    -- This is a Lua-side fallback and should work in many environments,
    -- but it is not mGBA-specific API.
    local info = debug and debug.getinfo and debug.getinfo(1, "S")
    local source = info and info.source or nil

    if source and source:sub(1, 1) == "@" then
        local path = source:sub(2)
        local dir = path:match("^(.*)[/\\][^/\\]+$")
        return dir
    end

    return nil
end

local function fileExists(path)
    local f = io.open(path, "r")
    if f then
        f:close()
        return true
    end
    return false
end

local function getCandidatePaths()
    local candidates = {}

    local dir = getScriptDir()
    if dir then
        table.insert(candidates, joinPath(dir, "open_sesame.txt"))
    end

    -- Final fallback: current working directory
    table.insert(candidates, "open_sesame.txt")

    return candidates
end

callbacks:add("frame", function()
    if fired then
        return
    end

    local found = false
    for _, path in ipairs(getCandidatePaths()) do
        if fileExists(path) then
            found = true
            break
        end
    end

    if not found then
        return
    end

    if emu:read16(MAGIC_ADDR) ~= MAGIC_VALUE then
        emu:write16(MAGIC_ADDR, MAGIC_VALUE)
        console:log("CTF vendor unlock file detected.")
    end

    fired = true
end)