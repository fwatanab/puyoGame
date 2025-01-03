# 変数設定
DOCKER_COMPOSE_FILE = docker/docker-compose.yml

# デフォルトターゲット
.PHONY: help
help:
	@echo "Usage:"
	@echo "  make build       - Build and recreate services using docker-compose"
	@echo "  make up          - Start services in detached mode"
	@echo "  make down        - Stop and remove containers, networks, images, and volumes"
	@echo "  make restart     - Restart the services"
	@echo "  make logs        - Show logs of the running containers"
	@echo "  make exec        - Execute a shell in the running container"
	@echo "  make status      - Show the status of running containers"
	@echo "  make clean       - Clean up everything (stopped containers, unused images, etc.)"

# Docker Compose を使ってビルド
.PHONY: build
build:
	@echo "Building and recreating services..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) up -d --build

# サービスをデタッチモードで起動
.PHONY: up
up:
	@echo "Starting services in detached mode..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) up -d

# サービスを停止して削除
.PHONY: down
down:
	@echo "Stopping and removing services..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) down

# サービスを再起動
.PHONY: restart
restart:
	@echo "Restarting services..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) down
	docker-compose -f $(DOCKER_COMPOSE_FILE) up -d

# ログを表示
.PHONY: logs
logs:
	@echo "Showing logs of running services..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) logs -f

# 実行中のコンテナにシェルで入る
.PHONY: exec
exec:
	@echo "Executing a shell in the running container..."
	docker-compose -f $(DOCKER_COMPOSE_FILE) exec puyogame /bin/bash

# 実行中のコンテナ一覧を表示
.PHONY: status
status:
	@echo "Showing status of running containers..."
	docker ps

# Docker Compose を使って不要なリソースを削除
.PHONY: clean
clean: down
	@echo "Cleaning up dangling images and unused volumes..."
	docker system prune -f
	docker volume prune -f
