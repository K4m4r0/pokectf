import tkinter as tk
from tkinter import messagebox


def trainer_code(trainer_id: int, name: str) -> int:
    s = (str(trainer_id) + name).encode("utf-8")
    x = 0
    for b in s:
        x ^= b
        x ^= (x << 3 & 0xFFFFFFFF)
        x ^= (x >> 5)
    x &= 0xFFFFFFFF
    return 1_000_000 + (x % 9_000_000)


def berechne_code():
    trainer_id_text = entry_trainer_id.get().strip()
    name_text = entry_name.get().strip()

    if not trainer_id_text:
        messagebox.showerror("Fehler", "Bitte eine Trainer_ID eingeben.")
        return

    if not name_text:
        messagebox.showerror("Fehler", "Bitte einen Namen eingeben.")
        return

    try:
        trainer_id = int(trainer_id_text)
    except ValueError:
        messagebox.showerror("Fehler", "Trainer_ID muss eine ganze Zahl sein.")
        return

    code = trainer_code(trainer_id, name_text)
    result_var.set(str(code))


root = tk.Tk()
root.title("Trainer Code Generator")
root.resizable(False, False)

main_frame = tk.Frame(root, padx=15, pady=15)
main_frame.pack()

tk.Label(main_frame, text="Trainer_ID:").grid(row=0, column=0, sticky="w", pady=(0, 8))
entry_trainer_id = tk.Entry(main_frame, width=30)
entry_trainer_id.grid(row=0, column=1, pady=(0, 8))

tk.Label(main_frame, text="Name:").grid(row=1, column=0, sticky="w", pady=(0, 8))
entry_name = tk.Entry(main_frame, width=30)
entry_name.grid(row=1, column=1, pady=(0, 8))

tk.Button(main_frame, text="Code berechnen", command=berechne_code).grid(
    row=2, column=0, columnspan=2, pady=(5, 10)
)

tk.Label(main_frame, text="Ergebnis:").grid(row=3, column=0, sticky="w")
result_var = tk.StringVar(value="")
tk.Entry(main_frame, textvariable=result_var, width=30, state="readonly").grid(row=3, column=1)

entry_trainer_id.focus()
root.bind("<Return>", lambda event: berechne_code())

if __name__ == "__main__":
    root.mainloop()