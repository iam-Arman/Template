rm ~/.config/nvim/init.lua
cat <<'EOF' > ~/.config/nvim/init.lua
-- ========================================================================== --
--    iamarman ULTIMATE CONFIG (Tokyo Night + Pro Features + Fixed Comments)  --
-- ========================================================================== --

-- 0. SILENCE WARNINGS
local _notify = vim.notify
vim.notify = function(msg, level, opts)
  if msg and (msg:match("deprecated") or msg:match("use vim.lsp.config")) then return end
  _notify(msg, level, opts)
end

-- 1. INSTALL PACKAGE MANAGER
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({ "git", "clone", "--filter=blob:none", "https://github.com/folke/lazy.nvim.git", "--branch=stable", lazypath })
end
vim.opt.rtp:prepend(lazypath)
vim.g.mapleader = " "

-- 2. PLUGINS
require("lazy").setup({
  -- === DASHBOARD (iamarman Edition) ===
  {
    "goolord/alpha-nvim",
    event = "VimEnter",
    config = function()
      local dashboard = require("alpha.themes.dashboard")
      dashboard.section.header.val = {
        " ███╗   ██╗██╗   ██╗██╗███╗   ███╗",
        " ████╗  ██║██║   ██║██║████╗ ████║",
        " ██╔██╗ ██║██║   ██║██║██╔████╔██║",
        " ██║╚██╗██║╚██╗ ██╔╝██║██║╚██╔╝██║",
        " ██║ ╚████║ ╚████╔╝ ██║██║ ╚═╝ ██║",
        " ╚═╝  ╚═══╝  ╚═══╝  ╚═╝╚═╝     ╚═╝",
        "          iamarman EDITION        ",
      }
      dashboard.section.buttons.val = {
        dashboard.button("n", "  New file", ":ene <BAR> startinsert <CR>"),
        dashboard.button("f", "  Find file", ":Telescope find_files <CR>"),
        dashboard.button("r", "  Recent", ":Telescope oldfiles <CR>"),
        dashboard.button("q", "  Quit", ":qa<CR>"),
      }
      require("alpha").setup(dashboard.opts)
    end,
  },

  -- === [NEW] SESSION MANAGER (Restores Tabs & Splits) ===
  {
    "rmagatti/auto-session",
    config = function()
      require("auto-session").setup({
        log_level = "error",
        auto_session_enable_last_session = true,
        auto_session_root_dir = vim.fn.stdpath('data').."/sessions/",
        auto_session_enabled = true,
        auto_save_enabled = true,
        auto_restore_enabled = true,
      })
    end
  },

  -- === [NEW] HARPOON (Fast Navigation) ===
  {
    "ThePrimeagen/harpoon",
    dependencies = { "nvim-lua/plenary.nvim" },
    config = function()
        local mark = require("harpoon.mark")
        local ui = require("harpoon.ui")
        vim.keymap.set("n", "<leader>a", mark.add_file, { desc = "Harpoon Add" })
        vim.keymap.set("n", "<C-e>", ui.toggle_quick_menu, { desc = "Harpoon Menu" })
        vim.keymap.set("n", "<C-1>", function() ui.nav_file(1) end)
        vim.keymap.set("n", "<C-2>", function() ui.nav_file(2) end)
        vim.keymap.set("n", "<C-3>", function() ui.nav_file(3) end)
        vim.keymap.set("n", "<C-4>", function() ui.nav_file(4) end)
    end
  },

  -- === VISUALS (TOKYO NIGHT) ===
  {
    "folke/tokyonight.nvim",
    lazy = false,
    priority = 1000,
    config = function()
      require("tokyonight").setup({
        style = "night",      -- Options: storm, night, moon, day
        transparent = true,   -- Enable glass effect
        terminal_colors = true,
      })
      vim.cmd.colorscheme("tokyonight")
    end,
  },

  { "stevearc/dressing.nvim", opts = {} },
  { "famiu/bufdelete.nvim" },
  { 
    'akinsho/bufferline.nvim', version = "*", dependencies = 'nvim-tree/nvim-web-devicons',
    opts = {
      options = {
        mode = "buffers", separator_style = "slant", always_show_bufferline = true,
        show_buffer_close_icons = true, show_close_icon = true,
        close_command = "Bdelete! %d", right_mouse_command = "Bdelete! %d",
      }
    }
  },
  { "lukas-reineke/indent-blankline.nvim", main = "ibl", opts = {} },
  { "nvim-lualine/lualine.nvim", opts = { options = { theme = "auto", section_separators = '', component_separators = '' } } },
  { "folke/noice.nvim", event = "VeryLazy", dependencies = { "MunifTanjim/nui.nvim" }, opts = { presets = { bottom_search = true, command_palette = true, long_message_to_split = true } } },

  -- === SEARCH & FILES ===
  { "VonHeikemen/searchbox.nvim", dependencies = { "MunifTanjim/nui.nvim" }, opts = {} },
  { "nvim-telescope/telescope.nvim", dependencies = { "nvim-lua/plenary.nvim" }, opts = {} },
  { "nvim-neo-tree/neo-tree.nvim", branch = "v3.x", dependencies = { "nvim-lua/plenary.nvim", "nvim-tree/nvim-web-devicons", "MunifTanjim/nui.nvim" } },
  { "akinsho/toggleterm.nvim", version = "*", config = function() require("toggleterm").setup({ direction = 'float', open_mapping = [[<c-\>]], float_opts = { border = 'curved', width = 100, height = 30 } }) end },

  -- === CP TOOLS ===
  {
    'xeluxee/competitest.nvim',
    dependencies = 'MunifTanjim/nui.nvim',
    config = function()
      require('competitest').setup({
        runner_ui = { viewer = { width = 0.5, height = 0.5 }, interface = "split" },
        compile_command = { cpp = { exec = "g++-15", args = { "-g", "-std=c++17", "$(FNAME)", "-o", "$(FNOEXT)" } } },
        run_command = { cpp = { exec = "./$(FNOEXT)" } },
      })
    end,
    keys = {
      { '<leader>rr', '<cmd>CompetiTest run<CR>', desc = "Run CP Tests" },
      { '<leader>ui', '<cmd>CompetiTest show_ui<CR>', desc = "View Test UI" },
    },
  },

  -- === DEBUGGING ===
  { "williamboman/mason.nvim", config = true },
  {
    "mfussenegger/nvim-dap",
    dependencies = { "rcarriga/nvim-dap-ui", "nvim-neotest/nvim-nio", "jay-babu/mason-nvim-dap.nvim" },
    config = function()
      local dap, dapui = require("dap"), require("dapui")
      dapui.setup()
      dap.listeners.before.attach.dapui_config = function() dapui.open() end
      dap.listeners.before.launch.dapui_config = function() dapui.open() end
      require("mason-nvim-dap").setup({ ensure_installed = { "codelldb" }, handlers = {} })
      dap.configurations.cpp = { { name = "Debug File", type = "codelldb", request = "launch", program = function() return vim.fn.expand('%:p:r') end, cwd = '${workspaceFolder}', stopOnEntry = false } }
      vim.keymap.set('n', '<F5>', function() require('dap').continue() end)
    end,
  },

  -- === AI & EDITOR ===
  { "Exafunction/codeium.vim", event = "BufEnter" },
   
  -- Treesitter (Safe Version)
  { 
    "nvim-treesitter/nvim-treesitter", 
    build = ":TSUpdate",
    event = { "BufReadPost", "BufNewFile" },
    config = function()
      local status_ok, configs = pcall(require, "nvim-treesitter.configs")
      if not status_ok then return end 
      configs.setup({ ensure_installed = { "cpp", "lua", "c" }, highlight = { enable = true } })
    end
  },
   
  { "numToStr/Comment.nvim", opts = {} },

  -- [FIXED HERE] FORCED COMPACT FORMATTING
  {
    "stevearc/conform.nvim",
    event = { "BufWritePre" },
    opts = {
      formatters = {
        ["clang-format"] = {
          -- Forced Google Style with Infinite Column Limit to prevent line splitting
          prepend_args = { 
            "--style={BasedOnStyle: Google, ColumnLimit: 0, AllowShortFunctionsOnASingleLine: All, BracedPadding: true}" 
          },
        },
      },
      formatters_by_ft = { cpp = { "clang-format" }, lua = { "stylua" } },
      format_on_save = { timeout_ms = 500, lsp_fallback = true },
    },
  },

  {
    "windwp/nvim-autopairs", event = "InsertEnter", dependencies = { "hrsh7th/nvim-cmp" },
    config = function()
      require("nvim-autopairs").setup({ check_ts = true, map_cr = true })
      local cmp_autopairs = require('nvim-autopairs.completion.cmp')
      local cmp = require('cmp')
      cmp.event:on('confirm_done', cmp_autopairs.on_confirm_done())
    end
  },

  -- === INTELLIGENCE ===
  { 
    "neovim/nvim-lspconfig", 
    config = function() 
      require("lspconfig").clangd.setup({
        cmd = { "clangd", "--background-index", "--query-driver=/usr/local/bin/g++*,/usr/bin/g++*,/opt/homebrew/bin/g++*" }
      }) 
    end 
  },
  { "L3MON4D3/LuaSnip", version = "v2.*", build = "make install_jsregexp" },
  { "rafamadriz/friendly-snippets" },
  { "saadparwaiz1/cmp_luasnip" },
  { 
    "hrsh7th/nvim-cmp", 
    dependencies = { "hrsh7th/cmp-nvim-lsp", "hrsh7th/cmp-buffer", "hrsh7th/cmp-path", "hrsh7th/cmp-cmdline", "onsails/lspkind.nvim" },
    config = function()
      local cmp = require('cmp')
      local luasnip = require('luasnip')
      require("luasnip.loaders.from_vscode").lazy_load()
      cmp.setup({
        snippet = { expand = function(args) luasnip.lsp_expand(args.body) end },
        formatting = { format = require('lspkind').cmp_format({ mode = 'symbol', symbol_map = { Codeium = "🤖" } }) },
        mapping = cmp.mapping.preset.insert({
          ['<Tab>'] = cmp.mapping(function(fallback) if cmp.visible() then cmp.select_next_item() elseif luasnip.expand_or_jumpable() then luasnip.expand_or_jump() else fallback() end end, {"i", "s"}),
          ['<S-Tab>'] = cmp.mapping(function(fallback) if cmp.visible() then cmp.select_prev_item() elseif luasnip.jumpable(-1) then luasnip.jump(-1) else fallback() end end, {"i", "s"}),
          ['<CR>'] = cmp.mapping.confirm({ select = true }),
        }),
        sources = cmp.config.sources({ { name = 'nvim_lsp' }, { name = 'luasnip' }, { name = 'buffer' } })
      })

      -- [NEW] Command Line Suggestions
      cmp.setup.cmdline(':', {
        mapping = cmp.mapping.preset.cmdline(),
        sources = cmp.config.sources({ { name = 'path' } }, { { name = 'cmdline' } })
      })
    end
  },
  {
    "folke/which-key.nvim", event = "VeryLazy",
    init = function() vim.o.timeout = true; vim.o.timeoutlen = 300 end,
    opts = {}
  },
})

-- 3. SETTINGS
vim.opt.number = true; vim.opt.relativenumber = true; 
vim.opt.mouse = "a"; 
vim.opt.clipboard = "unnamedplus"
vim.opt.splitright = true; vim.opt.splitbelow = true; 
vim.opt.tabstop = 4; vim.opt.shiftwidth = 4; vim.opt.expandtab = true
vim.opt.selectmode = 'mouse,key'
vim.opt.termguicolors = true
vim.opt.cursorline = true
vim.opt.updatetime = 300 
vim.opt.wrap = false

-- 4. KEYBINDINGS
local function smart_map(modes, key, result, is_operator)
    vim.keymap.set(modes, '<D-' .. key .. '>', result, { noremap = not is_operator, silent = true, remap = is_operator })
    vim.keymap.set(modes, '<M-' .. key .. '>', result, { noremap = not is_operator, silent = true, remap = is_operator })
end

smart_map({'n', 'i', 'v'}, 'z', '<Esc>u'); smart_map({'n', 'i', 'v'}, 'y', '<Esc><C-r>')
smart_map({'n', 'i', 'v'}, 'a', '<Esc>ggVG'); smart_map({'n', 'i', 'v'}, 's', '<Esc>:w<CR>')
smart_map('v', 'c', '"+y'); smart_map('v', 'x', '"+d'); smart_map({'n', 'v'}, 'v', '"+p')
vim.keymap.set('i', '<D-v>', '<C-r>+', { silent = true }); vim.keymap.set('i', '<M-v>', '<C-r>+', { silent = true })

-- [FIXED HERE] Separate Commenting Logic for Cmd+/
smart_map('n', '/', 'gcc', true)  -- Normal mode: Comment line
smart_map('v', '/', 'gc', true)   -- Visual mode: Comment selection

vim.keymap.set({'n', 'i'}, 'BS', '<Esc>ddi') 
vim.keymap.set('v', '<BS>', '"_d'); vim.keymap.set('v', '<Del>', '"_d')

vim.keymap.set('n', '<C-Up>', ':resize +2<CR>'); vim.keymap.set('n', '<C-Down>', ':resize -2<CR>')
vim.keymap.set('n', '<C-Left>', ':vertical resize -2<CR>'); vim.keymap.set('n', '<C-Right>', ':vertical resize +2<CR>')
vim.keymap.set('n', '<Tab>', ':BufferLineCycleNext<CR>', { silent = true })
vim.keymap.set('n', '<S-Tab>', ':BufferLineCyclePrev<CR>', { silent = true })
vim.keymap.set('n', '<leader>x', ':Bdelete!<CR>', { silent = true, desc = "Close Tab" })
vim.keymap.set('n', '<D-p>', require('telescope.builtin').find_files, {})
vim.keymap.set({'n', 'i'}, '<D-f>', ':SearchBoxMatchAll<CR>', { desc = "Find" })
vim.keymap.set({'n', 'i'}, '<C-f>', ':SearchBoxMatchAll<CR>', { desc = "Find" })
vim.keymap.set({'n', 'i'}, '<D-F>', ':SearchBoxReplace<CR>', { desc = "Replace" })
vim.keymap.set({'n', 'i'}, '<C-S-f>', ':SearchBoxReplace<CR>', { desc = "Replace" })
vim.keymap.set('n', '<leader>ff', require('telescope.builtin').find_files, {})
vim.keymap.set('n', '<F9>', ':w<CR>:vsplit | term g++-15 -g -std=c++17 % -o %< && ./%<<CR>')
vim.keymap.set('n', '<leader>e', ':Neotree toggle<CR>')

-- 5. AUTO-COMMANDS
vim.api.nvim_create_autocmd({ "InsertLeave", "FocusLost" }, {
  callback = function() if vim.bo.modified and vim.fn.getcmdtype() == "" then vim.cmd("silent! w") end end,
})

-- [NEW] ADVANCED TEMPLATE LOADER (Reads skeleton.cpp)
local group = vim.api.nvim_create_augroup("AutoTemplate", { clear = true })
vim.api.nvim_create_autocmd("BufNewFile", {
    pattern = "*.cpp",
    group = group,
    callback = function()
        local template_path = vim.fn.stdpath("config") .. "/templates/skeleton.cpp"
        local file = io.open(template_path, "r")
        if file then
            local content = file:read("*a")
            file:close()
            local lines = vim.split(content, "\n")
            vim.api.nvim_buf_set_lines(0, 0, -1, false, lines)
            vim.fn.search("void solve")
            vim.cmd("normal! j4>>") 
            vim.cmd("startinsert") 
        end
    end
})

-- [LEGACY] Keep your old keybind too just in case
vim.api.nvim_create_autocmd("FileType", { pattern = "cpp", callback = function()
    vim.keymap.set('i', '!cpp', "#include <bits/stdc++.h><CR>using namespace std;<CR><CR>void solve() {<CR><CR>}<CR><CR>int main() {<CR>ios_base::sync_with_stdio(false); cin.tie(NULL);<CR>solve();<CR>return 0;<CR>}<Esc>3ka", { buffer = true })
end })

vim.diagnostic.config({ virtual_text = true, signs = true, underline = true, update_in_insert = false })

-- Fix: Cmd+Delete (and Alt+Delete) removes the whole line
vim.keymap.set('n', '<D-BS>', 'dd', { silent = true })        -- Normal Mode
vim.keymap.set('i', '<D-BS>', '<Esc>ddi', { silent = true }) -- Insert Mode

-- MOUSE RESIZE
vim.keymap.set('n', '<C-ScrollWheelUp>', ':vertical resize +2<CR>', { silent = true })
vim.keymap.set('n', '<C-ScrollWheelDown>', ':vertical resize -2<CR>', { silent = true })
vim.keymap.set('n', '<M-ScrollWheelUp>', ':resize +2<CR>', { silent = true })
vim.keymap.set('n', '<M-ScrollWheelDown>', ':resize -2<CR>', { silent = true })

-- MOUSE TOGGLE
vim.keymap.set('n', '<leader>m', function()
  if vim.o.mouse == 'a' then
    vim.o.mouse = ''
    vim.notify("Mouse: DISABLED (Zoom/Select enabled)", "warn")
  else
    vim.o.mouse = 'a'
    vim.notify("Mouse: ENABLED (Neovim features on)", "info")
  end
end, { desc = "Toggle Mouse Support" })

-- DISABLE MOUSE (As you requested to stop garbage text)
vim.opt.mouse = ""
vim.opt.mouse = ""
vim.opt.mouse = ""
EOF
