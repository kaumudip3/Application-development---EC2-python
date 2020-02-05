from flask import Flask, request,flash,redirect,url_for,session
from os import urandom
from flask import render_template
from collections import Counter
from flask_mysqldb import MySQL
from MySQLdb import escape_string as thwart

app = Flask(__name__)

# DB config
app.config['MYSQL_HOST']='localhost'
app.config['MYSQL_USER']='root'
app.config['MYSQL_PASSWORD']='root'
app.config['MYSQL_DB']='user_db'

mysql = MySQL(app)

app.secret_key = urandom(24)

app.config['UPLOAD_FOLDER']='/flaskapp/userfile'

@app.route('/', methods=['GET','POST'])
def login():
    msg=''
    if request.method == 'POST':
        if request.form['btn']=="login":
            username = request.form['user']
            password = request.form['password']
            cur = mysql.connection.cursor()
            account = cur.execute("SELECT * FROM reg_table WHERE uname=%s AND pword=%s",(username,password))
            if account:
                session['user'] = username
                userdata = cur.fetchall()
                return render_template('users.html',userdata=userdata)
            else:
               msg = 'Incorrect username or password!'
        else:
            return redirect(url_for('register'))
    return render_template('login.html', msg=msg)

@app.route('/register/',methods=['POST','GET'])
def register():
    if request.method == 'POST':
        userdetails = request.form
        username = userdetails['user']
        passw = userdetails['password']
        firstname = userdetails['fname']
        lastname = userdetails['lname']
        mailid = userdetails['email']
        cur = mysql.connection.cursor()
        # Check if username taken
        resultuser = cur.execute("SELECT * FROM reg_table WHERE uname=(%s)",(thwart(username),))
        if int(resultuser) > 0:
            return 'User name already taken' #render_template('index.html')
        else:
            cur.execute("INSERT INTO reg_table(uname,pword,fname,lname,email) VALUES(%s,%s,%s,%s,%s)",(username,passw,firstname,lastname,mailid))
            mysql.connection.commit()
            cur.close()
            return 'Congratulations! New user registered! Please login to see your details.'
    return render_template('index.html')

@app.route('/signout')
def signout():
    session.pop('user')
    return redirect(url_for('login'))
@app.route('/user/')
def user():
    cur = mysql.connection.cursor()
    resultdata = cur.execute('SELECT * FROM reg_table')
    if resultdata > 0:
        userdata = cur.fetchall()
        return render_template('users.html',userdata=userdata)
    return 'Hello from Flask!'

@app.route('/user/',methods=['POST'])
def useroperation():
    if request.method == 'POST':
        if request.form['btn'] =='logout':
            return redirect(url_for('signout'))
        if request.form['btn'] == "fileupload":
            return redirect(url_for('fileupload'))
    return render_template('login.html')

@app.route('/fileupload/',methods=['POST'])
def file_upload():
    if request.method=='POST':
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
            file = request.files['file']
            if file.filename == '':
                flash('No file selected for uploading')
                return redirect(request.url)
            if file:
               flash('No file selected for uploading')
                return redirect(request.url)
            if file:
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                flash('File successfully uploaded')
                return redirect('/fileupload/')
            else:
                flash('Allowed file types are txt, pdf, png, jpg, jpeg, gif')
                return redirect(request.url)
    return render_template('fileupload.html')

@app.route('/countme/<input_str>')
def count_me(input_str):
    input_counter = Counter(input_str)
    response = []
    for letter, count in input_counter.most_common():
        response.append('"{}": {}'.format(letter, count))
        return '<br>'.join(response)

if __name__ == '__main__':
  app.run(debug=True)
