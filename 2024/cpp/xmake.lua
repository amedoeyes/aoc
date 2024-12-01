set_languages("c++23")
set_warnings("allextra", "pedantic", "error")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd", outputdir = "build" })

for _, file in ipairs(os.files("days/**.cpp")) do
	local name = path.basename(file)
	local parent = path.directory(file):match("([^/]+)/?$")
	target(parent .. "_" .. name, { files = file, includedirs = "./" })
end
