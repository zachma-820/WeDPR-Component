from ppc_scheduler.workflow.worker.worker import Worker


class ApiWorker(Worker):

    def __init__(self, components, job_context, worker_id, worker_type, *args, **kwargs):
        super().__init__(components, job_context, worker_id, worker_type, *args, **kwargs)

    def engine_run(self, worker_inputs):
        ...