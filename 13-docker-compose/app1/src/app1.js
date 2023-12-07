import os      from 'node:os';
import express from 'express';

const NODE_PORT   = process.env["NODE_PORT"];

if (!NODE_PORT) {
	process.stderr.write("ERROR: missing NODE_PORT configuration variable\n");
	process.exitCode = 1;
} else {
	const app = express();
	app.get("/", getHome);
	app.listen(NODE_PORT);
}

async function getHome(req, res) {
	const host = os.hostname();
	const port = NODE_PORT;

	const homePage = `
		<html>
			<body>
				<h1>TVS App 1</h1>
				<hr>
				<strong>HOST: </strong>${ host }<br>
				<strong>PORT: </strong>${ port }<br>
			</body>
		</html>
	`;
	res.send(homePage);
}

