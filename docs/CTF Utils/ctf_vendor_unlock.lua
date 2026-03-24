-- =========================
-- ctf_vendor_unlock.lua
-- ROM, this Lua and open_sesame.txt have to be in the same folder.
-- =========================

local MAGIC_ADDR  = 0x02000AD2
local MAGIC_VALUE = 0xC7F7

-- File only has to exist, content does not matter
local FLAG_FILE = script.dir .. "/open_sesame.txt"

local fired = false

callbacks:add("frame", function()
    if fired then
        return
    end

    local f = io.open(FLAG_FILE, "r")
    if not f then
        return
    end
    f:close()

    -- Write only once per session
    if emu:read16(MAGIC_ADDR) ~= MAGIC_VALUE then
        emu:write16(MAGIC_ADDR, MAGIC_VALUE)
        console:log("CTF vendor unlock file detected.")
    end

    fired = true
end)