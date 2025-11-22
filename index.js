const form = document.createElement("form");
const edgeCount = document.getElementById("edgeCount");
const okBtn = document.getElementById("okBtn");

class Graph {
    constructor() {
        this.adjacencyList = new Map();
    }

    addVertex(vertex) {
        if (!this.adjacencyList.has(vertex)) {
            this.adjacencyList.set(vertex, []);
        }
    }

    addEdge(source, target) {
        this.addVertex(source);
        this.addVertex(target);
        this.adjacencyList.get(source).push(target);
        this.adjacencyList.get(target).push(source);
    }
}

const generateEdgeFields = (count) => {
    form.id = "vertexForm";
    form.method = "POST";

    const submitButton = document.createElement("button");
    submitButton.id = "submitButton";
    submitButton.textContent = "Submit";
    submitButton.type = "submit";

    edgeCount.after(form);

    if (!edgeCount || !okBtn) return;

    for (let i = 0; i < count; i++) {
        const vertexField = document.createElement("div");
        vertexField.innerHTML = `Source: <input class="vertexField" type="text">
                                 Target: <input class="vertexField" type="text"/>
                                 <br><br>`;
        form.append(vertexField);
    }

    const shortestPathField = document.createElement("div");
    shortestPathField.class = "shortestPath";
    shortestPathField.innerHTML = `
                                   <h3>
                                   Get shortest path<br><br>
                                   Source: <input class="shortestPathSource" type="text">
                                   Target: <input class="shortestPathTarget" type="text">
                                   </h3>`;
    form.append(shortestPathField);
    form.append(submitButton);

    const edgeCountDiv = document.createElement("div");
    edgeCountDiv.innerHTML = `<h3>Edge count: ${edgeCount.value}</h3>`

    edgeCount.remove();
    okBtn.remove();
};

const addEdgesFromFields = (graph) => {
    const edgeFields = form.getElementsByTagName("div");
    for (let edgeField of edgeFields) {
        const vertexFields = edgeField.getElementsByClassName("vertexField");
        if (vertexFields.length >= 2) {
            const source = vertexFields[0].value;
            const target = vertexFields[1].value;
            graph.addEdge(source, target);
        }
    }
}

const getShortestPathFormField = () => {
    const edgeFields = form.getElementsByTagName("div");
    const selectedVertexFields = edgeFields[edgeFields.length - 1];
    const sourceInputs = selectedVertexFields.getElementsByClassName("shortestPathSource");
    const targetInputs = selectedVertexFields.getElementsByClassName("shortestPathTarget");
    if (sourceInputs.length > 0 && targetInputs.length > 0) {
        return {
            source: sourceInputs[0].value,
            target: targetInputs[0].value
        };
    }
    return null;
}

form.onsubmit = async (event) => {
    event.preventDefault();
    const graph = new Graph();
    addEdgesFromFields(graph);
    selectedVertexes = getShortestPathFormField();
    const bodyParams = {
        "graph": Object.fromEntries(graph.adjacencyList),
        "edges": [
            selectedVertexes.source,
            selectedVertexes.target
        ]
    };
    const response = await fetch("http://localhost:18080/get_shortest_path", {
        method: "POST",
        body: JSON.stringify(bodyParams),
        headers: {
            "Content-Type": "application/json",  // ✅ Обязательно!
        },
    });
    const json = await response.json();
    console.log(json);
}
