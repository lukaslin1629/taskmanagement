import csv
import os

try:
    import bcrypt
except ImportError:
    import subprocess
    import sys
    print("bcrypt not found. Installing...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "bcrypt"])
    import bcrypt

CSV_FILE = "users.csv"

def load_users():
    user_db = {}
    if os.path.exists(CSV_FILE):
        with open(CSV_FILE, mode="r", newline="") as file:
            reader = csv.reader(file)
            for row in reader:
                if len(row) == 2:
                    un, hashed_pw = row
                    try:
                        user_db[un] = bytes.fromhex(hashed_pw)
                    except ValueError:
                        print(f"Warning: corrupted hash for user {un}")
    return user_db

def save_user(un, hashed_pw):
    with open(CSV_FILE, mode="a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([un, hashed_pw.hex()])
        file.flush()
        os.fsync(file.fileno())

def register_user(user_db, un, pw):
    if un in user_db:
        print("User already exists.")
        return False
    salt = bcrypt.gensalt()
    hashed_pw = bcrypt.hashpw(pw.encode("utf-8"), salt)
    user_db[un] = hashed_pw
    save_user(un, hashed_pw)
    print(f"User {un} registered successfully.")
    return True

def authenticate_user(user_db, un, pw):
    if un in user_db:
        stored_pw = user_db[un]
        try:
            if bcrypt.checkpw(pw.encode("utf-8"), stored_pw):
                print(f"User {un} logged in successfully.")
                return True
        except ValueError:
            print("Corrupted stored password.")
    print("Invalid username or password.")
    return False

if __name__ == "__main__":
    user_db = load_users()
    is_first_user = len(user_db) == 0

    if is_first_user:
        print("No users found. Please register a new user.")
        username = input("Enter new username: ").strip()
        password = input("Enter new password: ").strip()
        if register_user(user_db, username, password):
            print("Registration complete.")
        exit(2)
    else:
        print("Please log in.")
        username = input("Enter username: ").strip()
        password = input("Enter password: ").strip()

        user_db = load_users()

        if authenticate_user(user_db, username, password):
            exit(0)
        else:
            exit(1)
