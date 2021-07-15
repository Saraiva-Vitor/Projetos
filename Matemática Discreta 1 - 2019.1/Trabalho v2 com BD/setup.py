import sys
from cx_Freeze import setup, Executable
import Tkinter

base = None
if sys.platform == "win32":
    base = "Win32GUI"

executables = [
        Executable("trabalhomatdiscreta1_v2.py", base=base)
]

buildOptions = dict(
        packages = ["Tkinter"],
        includes = ["Tkinter"],
        include_files = [],
        excludes = []
)




setup(
    name = "CalculadoraFinanceira",
    version = "2.0",
    description = "Calculadora Financeira das tabelas SAC e Price",
    options = dict(build_exe = buildOptions),
    executables = executables
 )
