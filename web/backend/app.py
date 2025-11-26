from flask import Flask, jsonify, request
import sqlite3

app = Flask(__name__)
DB = "aegis.db"

@app.route("/documents", methods=["GET"])
def list_documents():
    conn = sqlite3.connect(DB)
    cur = conn.cursor()
    cur.execute("SELECT id, title, author, tags FROM documents")
    docs = [{"id": row[0], "title": row[1], "author": row[2], "tags": row[3].split(",")} for row in cur.fetchall()]
    conn.close()
    return jsonify(docs)

@app.route("/document/<int:doc_id>/versions", methods=["GET"])
def list_versions(doc_id):
    conn = sqlite3.connect(DB)
    cur = conn.cursor()
    cur.execute("SELECT versionId, content, timestamp FROM versions WHERE docId=?", (doc_id,))
    vers = [{"versionId": row[0], "content": row[1], "timestamp": row[2]} for row in cur.fetchall()]
    conn.close()
    return jsonify(vers)

@app.route("/document/search", methods=["GET"])
def search():
    q = request.args.get("q", "")
    like = f"%{q}%"
    conn = sqlite3.connect(DB)
    cur = conn.cursor()
    cur.execute("SELECT id, title, author, tags FROM documents WHERE title LIKE ? OR tags LIKE ?", (like, like))
    res = [{"id": row[0], "title": row[1], "author": row[2], "tags": row[3].split(",")} for row in cur.fetchall()]
    conn.close()
    return jsonify(res)

if __name__ == "__main__":
    app.run(debug=True)
