from telegram import Update
from telegram.ext import Updater, CommandHandler, CallbackContext


def hello(update: Update, context: CallbackContext) -> None:
    update.message.reply_text(f'Hello {Salahuddin}')


updater = Updater('2018298659:AAEqwAd6NMALOtHU3nAn7wuEOT5f4hXuEP0')

updater.dispatcher.add_handler(CommandHandler('hello', hello))

updater.start_polling()
updater.idle()

