-- ========================================================================== --
--   THE FINAL CONFIG (Performance Optimized: No Lag)                         --
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
  { "tanvirtin/monokai.nvim", lazy = false, priority = 1000, config = function() require("monokai").setup() end },
  { "nvim-lualine/lualine.nvim", opts = { options = { theme = "auto", section_separators = '', component_separators = '' } } },
  { "folke/noice.nvim", event = "VeryLazy", dependencies = { "MunifTanjim/nui.nvim" }, opts = { presets = { bottom_search = true, command_palette = true, long_message_to_split = true } } },
  { "VonHeikemen/searchbox.nvim", dependencies = { "MunifTanjim/nui.nvim" }, opts = {} },
  { "nvim-telescope/telescope.nvim", dependencies = { "nvim-lua/plenary.nvim" }, opts = {} },
  { "nvim-neo-tree/neo-tree.nvim", branch = "v3.x", dependencies = { "nvim-lua/plenary.nvim", "nvim-tree/nvim-web-devicons", "MunifTanjim/nui.nvim" } },
  { "akinsho/toggleterm.nvim", version = "*", config = function() require("toggleterm").setup({ direction = 'float', open_mapping = [[<c-\>]], float_opts = { border = 'curved', width = 100, height = 30 } }) end },

  -- C++ Runner (Using g++-15)
  {
    'xeluxee/competitest.nvim',
    dependencies = 'MunifTanjim/nui.nvim',
    config = function()
      require('competitest').setup({
        runner_ui = { viewer = { width = 0.5, height = 0.5 } },
        compile_command = { cpp = { exec = "g++-15", args = { "-g", "-std=c++17", "$(FNAME)", "-o", "$(FNOEXT)" } } },
        run_command = { cpp = { exec = "./$(FNOEXT)" } },
      })
    end,
    keys = {
      { '<leader>rr', '<cmd>CompetiTest run<CR>', desc = "Run CP Tests" },
      { '<leader>ui', '<cmd>CompetiTest show_ui<CR>', desc = "View Test UI" },
    },
  },

  -- Debugging
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

  -- AI & Syntax
  { "Exafunction/codeium.vim", event = "BufEnter" },
  { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate" },
  { "numToStr/Comment.nvim", opts = {} },
  { "windwp/nvim-autopairs", event = "InsertEnter", opts = {} },

  -- INTELLIGENCE
  { 
    "neovim/nvim-lspconfig", 
    config = function() 
      require("lspconfig").clangd.setup({
        cmd = {
          "clangd",
          "--background-index",
          "--query-driver=/usr/local/bin/g++*,/usr/bin/g++*,/opt/homebrew/bin/g++*"
        }
      }) 
    end 
  },
  { 
    "hrsh7th/nvim-cmp", 
    dependencies = { "hrsh7th/cmp-nvim-lsp", "hrsh7th/cmp-buffer", "hrsh7th/cmp-path", "hrsh7th/cmp-cmdline", "onsails/lspkind.nvim" },
    config = function()
      local cmp = require('cmp')
      cmp.setup({
        formatting = { format = require('lspkind').cmp_format({ mode = 'symbol', symbol_map = { Codeium = "🤖" } }) },
        mapping = cmp.mapping.preset.insert({ ['<Tab>'] = cmp.mapping.select_next_item(), ['<CR>'] = cmp.mapping.confirm({ select = true }) }),
        sources = cmp.config.sources({ { name = 'nvim_lsp' }, { name = 'buffer' } })
      })
      cmp.setup.cmdline(':', {
        mapping = cmp.mapping.preset.cmdline({
          ['<Tab>'] = { c = function() if cmp.visible() then cmp.select_next_item() else cmp.complete() end end },
          ['<S-Tab>'] = { c = function() if cmp.visible() then cmp.select_prev_item() else cmp.complete() end end },
          ['<Down>'] = { c = function() if cmp.visible() then cmp.select_next_item() else cmp.complete() end end },
          ['<Up>'] = { c = function() if cmp.visible() then cmp.select_prev_item() else cmp.complete() end end },
          ['<CR>'] = { c = cmp.mapping.confirm({ select = false }) }, 
        }),
        sources = cmp.config.sources({ { name = 'path' } }, { { name = 'cmdline' } })
      })
      cmp.setup.cmdline('/', { mapping = cmp.mapping.preset.cmdline(), sources = { { name = 'buffer' } } })
    end
  },
})

-- 3. SETTINGS (LAG FIXED HERE)
pcall(function() require'nvim-treesitter.configs'.setup { ensure_installed = { "cpp", "lua" }, highlight = { enable = true } } end)
vim.opt.number = true; vim.opt.relativenumber = true; vim.opt.mouse = "a"; vim.opt.clipboard = "unnamedplus"
vim.opt.splitright = true; vim.opt.splitbelow = true; vim.opt.tabstop = 4; vim.opt.shiftwidth = 4; vim.opt.expandtab = true
vim.opt.selectmode = 'mouse,key'

-- FIXED: Increased delay to 300ms to stop lag
vim.opt.updatetime = 300 

-- 4. KEYBINDINGS
local function smart_map(modes, key, result, is_operator)
    vim.keymap.set(modes, '<D-' .. key .. '>', result, { noremap = not is_operator, silent = true, remap = is_operator })
    vim.keymap.set(modes, '<M-' .. key .. '>', result, { noremap = not is_operator, silent = true, remap = is_operator })
end

smart_map({'n', 'i', 'v'}, 'z', '<Esc>u'); smart_map({'n', 'i', 'v'}, 'y', '<Esc><C-r>')
smart_map({'n', 'i', 'v'}, 'a', '<Esc>ggVG'); smart_map({'n', 'i', 'v'}, 's', '<Esc>:w<CR>')
smart_map('v', 'c', '"+y'); smart_map('v', 'x', '"+d'); smart_map({'n', 'v'}, 'v', '"+p')
vim.keymap.set('i', '<D-v>', '<C-r>+', { silent = true }); vim.keymap.set('i', '<M-v>', '<C-r>+', { silent = true })
smart_map({'n', 'v'}, '/', 'gc', true) 
vim.keymap.set({'n', 'i'}, 'BS', '<Esc>ddi') 
vim.keymap.set('v', '<BS>', '"_d'); vim.keymap.set('v', '<Del>', '"_d')

vim.keymap.set('n', '<C-Up>', ':resize +2<CR>'); vim.keymap.set('n', '<C-Down>', ':resize -2<CR>')
vim.keymap.set('n', '<C-Left>', ':vertical resize -2<CR>'); vim.keymap.set('n', '<C-Right>', ':vertical resize +2<CR>')

vim.keymap.set({'n', 'i'}, '<D-f>', ':SearchBoxMatchAll<CR>', { desc = "Find" })
vim.keymap.set({'n', 'i'}, '<C-f>', ':SearchBoxMatchAll<CR>', { desc = "Find" })
vim.keymap.set({'n', 'i'}, '<D-F>', ':SearchBoxReplace<CR>', { desc = "Replace" })
vim.keymap.set({'n', 'i'}, '<C-S-f>', ':SearchBoxReplace<CR>', { desc = "Replace" })
vim.keymap.set('n', '<leader>ff', require('telescope.builtin').find_files, {})

-- F9 uses g++-15
vim.keymap.set('n', '<F9>', ':w<CR>:vsplit | term g++-15 -g -std=c++17 % -o %< && ./%<<CR>')
vim.keymap.set('n', '<leader>e', ':Neotree toggle<CR>')

-- 5. AUTO-COMMANDS (SMARTER SAVE)
-- FIXED: Removed "CursorHold" to stop stuttering while typing.
-- Now saves only when you leave Insert Mode or Switch Windows.
vim.api.nvim_create_autocmd({ "InsertLeave", "FocusLost" }, {
  callback = function() if vim.bo.modified and vim.fn.getcmdtype() == "" then vim.cmd("silent! w") end end,
})

vim.api.nvim_create_autocmd("FileType", { pattern = "cpp", callback = function()
    vim.keymap.set('i', '!cpp', "#include <bits/stdc++.h><CR>using namespace std;<CR><CR>void solve() {<CR><CR>}<CR><CR>int main() {<CR>ios_base::sync_with_stdio(false); cin.tie(NULL);<CR>solve();<CR>return 0;<CR>}<Esc>3ka", { buffer = true })
end })

-- FIXED: Don't update errors while typing (prevents lag)
vim.diagnostic.config({ 
  virtual_text = true, 
  signs = true, 
  underline = true,
  update_in_insert = false 
})
