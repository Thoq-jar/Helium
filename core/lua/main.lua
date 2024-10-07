--[[
-- Purrooser
-- File: main.lua
-- Purpose: Main stuff for Purrooser browser
-- License: MIT
-- (C) Thoq
]]--

---------------- Create The User Interface ----------------
function CreateUI (renderer)
    Log("Setting up Purrooser [1/9]")
    local toolbar = renderer:addToolBar("Main Toolbar") -- Create Toolbar --

    Log("Setting up Purrooser [2/9]")
    local back_button = renderer:addButton(toolbar, "<", function() renderer:back() end) -- Create Back Button --
    
    Log("Setting up Purrooser [3/9]")
    local forward_button = renderer:addButton(toolbar, ">", function() renderer:forward() end) -- Create Forward Button --

    Log("Setting up Purrooser [4/9]")
    local reload_button = renderer:addButton(toolbar, "↻", function() renderer:reload() end) -- Create Reload Button --

    Log("Setting up Purrooser [5/9]")
    local home_button = renderer:addButton(toolbar, "⌂", function() renderer:load_local_file() end) -- Create Home Button --

    Log("Setting up Purrooser [6/9]")
    local url_bar = renderer:addUrlBar(toolbar, function() renderer:navigate_to_url() end) -- Create URL Bar --

    Log("Setting up Purrooser [7/9]")
    local new_tab_button = renderer:addButton(toolbar, "+", function() renderer:add_new_tab() end) -- Create Add Button --

    Log("Setting up Purrooser [8/9]")
    local close_tab_button = renderer:addButton(toolbar, "X", function() renderer:close_current_tab() end) -- Create Close Button --

    -- Check If On Linux / FreeBSD --
    Log("Setting up Purrooser [9/9]")
    if renderer:is_dark_mode_supported() then
        -- If So, Create Dark Mode Toggle --
        local toggle_button = renderer:addButton(toolbar, "🌙", function() renderer:toggle_dark_light_mode() end)
    end

    Log("Purrooser set up successfully!")
    Log("[9/9] Operations completed sucessfully!")
    io.write('\n') -- Make Newline For Cleaner Viewing --
end

---------------- Logging ----------------
function Log (message)
    print(" [LOG/MAIN] " .. message) -- Log The Message --
end

---------------- Print Information About Purrooser ----------------
function PrintInfo ()
    io.write('\n') -- Make Newline For Cleaner Viewing --
    print("-------------------------------- Information --------------------------------")
    Log("Purrooser")
    Log("v0.1.27 {Nightly}")

    io.write('\n') -- Make Newline For Cleaner Viewing --
    print("-------------------------------- Legal --------------------------------")
    Log("License: MIT")
    Log("You should have received a copy of the MIT License!")
    Log("If you didnt, you can obtain a copy here: https://raw.githubusercontent.com/Thoq-jar/Purrooser/refs/heads/main/LICENSE")

    io.write('\n') -- Make Newline For Cleaner Viewing --
    print("-------------------------------- Logs --------------------------------")
    Log("Setting up Purrooser [0/9]")

    io.flush() -- Flush Any Pending Operations --
end
