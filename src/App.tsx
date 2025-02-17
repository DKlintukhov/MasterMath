import { Routes, Route, useNavigate, useLocation } from "react-router-dom";
import { Container } from "@mui/material";
import { Exercise, ExerciseSetup, Results } from "./pages";
import { useEffect, useState } from "react";
import { Expression } from "./models";

export function App() {
    const navigate = useNavigate();
    const location = useLocation();
    const [expressions, setExpressions] = useState<Expression[]>([]);
    const [timeout, setTimeout] = useState<number>(0);

    const exerciseStarted = (timeout: number, expressions: Expression[]) => {
        setTimeout(timeout);
        setExpressions(expressions);
        navigate("/exercise");
    }

    const exerciseFinished = (duration: number, answers: number[]) => {
        console.log(duration, answers);
        navigate("/results");
    }

    const finished = () => {
        navigate("/");
    }

    useEffect(() => {
        if (location.pathname !== "/") {
            navigate("/");
        }
    }, []);

    return (
        <Container maxWidth="md"
            style={{
                height: "100vh",
                width: "100vw",
                display: "flex",
                justifyContent: "center",
                alignItems: "center",
                overflow: "hidden"
            }}>
            <Routes>
                <Route path="/" element={<ExerciseSetup onStarted={exerciseStarted} />} />
                <Route path="/exercise" element={<Exercise timeout={timeout} expressions={expressions} onFinished={exerciseFinished} />} />
                <Route path="/results" element={<Results onFinished={finished} />} />
            </Routes>
        </Container>

    );
}
