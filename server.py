from flask import Flask, request, jsonify

app = Flask(_name_)

@app.route('/post-data', methods=['POST', 'GET'])
def post_data():
    data = request.json
    if not data:
        return jsonify({'error': 'No data provided'}), 400
    
    temperature = data.get('temperature')
    humidity = data.get('humidity')
    
    if temperature is None or humidity is None:
        return jsonify({'error': 'Invalid data'}), 400

    print(f"Received data - Temperature: {temperature}, Humidity: {humidity}")
    
    return jsonify({'message': 'Data received successfully'}), 200

if _name_ == '_main_':
    app.run(host='0.0.0.0', port=5000, debug=True)